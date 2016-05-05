#include "class/game/chessMaster/chessboard/ChessBoard.h"
#include "class/display/draw/Draw.h"
#include "class/display/draw/drawObject/drawData/DrawDataObj.h"
#include "class/input/Input.h"
#include "class/tim/string/String.h"
#include "class/display/texture/AllTextures.h"
#include "class/display/model/modelBuffer/AllModelBuffers.h"
#include "class/display/draw/drawObject/AllDrawObjects.h"
#include <fstream>
#include <iostream>
#include <cmath>
namespace CM {

ChessBoard::ChessBoard(int sizex,int sizey,int sizez) {
	cube_size=1.0;
	board=0;
	chess_board=0;
	cur_board=0;
	rule=0;
	cube_type_num=3;
	mct = 0;
	cur_node=0;
	model_map=0;
	tex_map=0;
	draw_map=0;
	game_name="unknown chess game";
	dboard = new Display::DynamicDrawObject();
	Display::Draw::get_cur_object()->push(dboard);//remember to remove before delete dboard
	pos = new Position(glm::vec3(0, 0, 0), glm::vec3());
	cube = new Display::CubeModel(0.5*cube_size);

	dboard->init_drawObject("","","",true);
	size.x=sizex;
	size.y=sizey;
	size.z=sizez;
	init_board();

	register_cur();
}
ChessBoard::~ChessBoard() {
	clear();

	Display::Draw::get_cur_object()->remove(dboard);
	remove_drawobject();
	delete dboard;
	delete pos;
	delete cube;
}
void ChessBoard::clear(){
	save_mct();
	for(unsigned i=0;i<pieces.size();i++)delete pieces.at(i);
	pieces.clear();
	clear_steps();
	winner=0;
	cur_player=1;

	if(board){
		delete board;
		board=0;
	}
	if(chess_board){
		delete chess_board;
		chess_board=0;
	}
	if(rule){
		delete rule;
		rule=0;
	}
	if(mct){
		delete mct;
		mct=0;
	}
}
void ChessBoard::init_board(){
	if(board){
		delete board;
		board=0;
	}
	if(chess_board){
		delete chess_board;
		chess_board=0;
	}
	clear_steps();
	board=new Tim::Array3D<unsigned char>(size.x,size.y,size.z);
	//chess_board=new Tim::Array2D<short int>(size.x,size.z);
	chess_board=new CM::Board<short int>(size.x,size.z,pieces.size());
	for(int i=0;i<board->sizex;i++){
		for(int j=0;j<board->sizey;j++){
			for(int k=0;k<board->sizez;k++){
				if(j==0){
					board->get(i,j,k)=1;//button of the board
				}else{
					board->get(i,j,k)=0;
				}
			}
		}
	}


	updated=true;
	winner=0;
	cur_player=1;
}
void ChessBoard::init_pieces(){
	for(unsigned i=0;i<pieces.size();i++){
		pieces_weight[i]=pieces.at(i)->weight;
	}
}
int ChessBoard::find_board(lua_State *L){
	lua_getglobal(L, "board");
	CM::Board<short int> *cb =(CM::Board<short int>*)lua_touserdata(L,-1);
	lua_pop(L,1);
	int type = lua_tonumber(L, -1);
	lua_pop(L,1);
	int total=0;
	for(int i=0;i<cb->sizex;i++){
		for(int j=0;j<cb->sizey;j++){
			if(cb->get(i,j)==type){
				total++;
			}
		}
	}
	lua_pushnumber(L,total);
	return 1;
}
int ChessBoard::get_board(lua_State *L){
	//std::cout<<"ChessBoard::get_board"<<std::endl;

	lua_getglobal(L, "board");
	CM::Board<short int> *cb =(CM::Board<short int>*)lua_touserdata(L,-1);
	lua_pop(L,1);

	int y = lua_tonumber(L, -1);
	lua_pop(L,1);
	int x = lua_tonumber(L, -1);
	lua_pop(L,1);


	int type=cb->get(x,y);;

	lua_pushnumber(L,type);

	return 1;
}
int ChessBoard::get_chess_num_delta(lua_State *L){
	lua_getglobal(L, "board");
	CM::Board<short int> *cb =(CM::Board<short int>*)lua_touserdata(L,-1);
	lua_pop(L,1);

	int type = lua_tonumber(L, -1);
	lua_pop(L,1);

	int num=0;
	if(type>0){
		num=cb->piece_num[type-1];
	}else if(type<0){
		num=-cb->piece_num[-type-1];
	}

	lua_pushnumber(L,num);

	return 1;
}
bool ChessBoard::bound_check(int x,int y){
	if(x<0||y<0||x>=chess_board->sizex||y>=chess_board->sizey){
		return false;
	}
	return true;
}
bool ChessBoard::set_type(int x,int y,short int val){
	if(x<0||y<0||x>=chess_board->sizex||y>chess_board->sizey){
		return false;
	}
	chess_board->get(x,y)=val;
	return true;
}
int ChessBoard::get_type(int x,int y){
	/*
	if(x<0||y<0||x>=chess_board->sizex||y>chess_board->sizey){
		std::cerr<<"ChessBoard::get_type out of range"<<x<<","<<y<<std::endl;
		return 0;
	}
	*/
	return chess_board->get(x,y);
}
Piece* ChessBoard::get_piece(int x,int y){
	int type=get_type(x,y);
	if(type==0)return 0;

	if(type<0)type*=-1;
	return pieces.at(type-1);
}
int ChessBoard::get_type(int x,int y,int z){
	if(x<0||y<0||z<0||x>=board->sizex||y>=board->sizey||z>board->sizez){
		return -1;
	}
	return board->get(x,y,z);
}
bool ChessBoard::set_type(int x,int y,int z,unsigned char val){
	if(x<0||x>=board->sizex||y<0||y>=board->sizey||z<0||z>=board->sizez){
		std::cout<<"ChessBoard::set_type out of range"<<"x="<<x<<"y="<<y<<"z="<<z<<std::endl;
		return false;
	}
	board->get(x,y,z)=val;
	updated=true;
	return true;
}
void ChessBoard::load_script(std::string path){
	clear();
	std::filebuf file;
	file.open(path.c_str(), std::ios::in);
	if (!file.is_open()) {
		std::cerr << "ChessBoard::load_script fail,file:" << path
				<< " open fail" << std::endl;
		return;
	}
	std::istream is(&file);
	std::string line;

	if(Tim::String::get_line(is, line, true, true)&&line=="dir_path:"){
		Tim::String::get_line(is,dir_path, true, true);
	}else{
		std::cerr << "ChessBoard::load_script fail,no board_path:" <<std::endl;
	}
	if(Tim::String::get_line(is, line, true, true)&&line=="game_name:"){
		Tim::String::get_line(is,game_name, true, true);
	}else{
		std::cerr << "ChessBoard::load_script fail,no game_name:" <<std::endl;
	}
	init_drawobject();
	load_pieces(dir_path+"chessBoard/pieces.txt");
	load_board(dir_path+"chessBoard/board.txt");



	if(Tim::String::get_line(is, line, true, true)&&line=="texture:"){
		Tim::String::get_line(is, tex_path, true, true);
	}
	if(Tim::String::get_line(is, line, true, true)&&line=="normal_texture:"){
		Tim::String::get_line(is, normal_path, true, true);
	}
	if(Tim::String::get_line(is, line, true, true)&&line=="cube_type_num:"){
		Tim::String::get_line(is, line, true, true);
		sscanf(line.c_str(),"%d",&cube_type_num);
	}
	//if(dboard)delete dboard;
	//dboard = new DynamicDrawObject();
	//std::cout<<"ChessBoard::load_script tex_path="<<tex_path<<std::endl;
	dboard->init_drawObject("",tex_path,normal_path,true);

	if(rule)delete rule;
	rule=new CM::Rule();
	rule->load_rule(dir_path+"chessBoard/rule.lua");

	load_mct();


	file.close();
}
void ChessBoard::init_drawobject(){

	model_map=new Display::ModelBufferMap();
	model_map->folder_path=dir_path+"model/";
	model_map->Load_script(dir_path+"model/models.txt");
	Display::AllModelBuffers::get_cur_object()->push_map(model_map);

	tex_map=new Display::TextureMap(dir_path+"textures/textures.txt");
	Display::AllTextures::get_cur_object()->push_map(tex_map);

	draw_map=new Display::DrawObjectMap(dir_path+"drawobject/chess.txt");
	Display::AllDrawObjects::get_cur_object()->push_map(draw_map);
}
void ChessBoard::remove_drawobject(){
	Display::AllModelBuffers::get_cur_object()->remove_map(model_map);
	Display::AllTextures::get_cur_object()->remove_map(tex_map);
	Display::AllDrawObjects::get_cur_object()->remove_map(draw_map);
}
void ChessBoard::save_pieces(std::string path){

}
void ChessBoard::load_pieces(std::string path){
	std::filebuf file;
	file.open(path.c_str(), std::ios::in);
	if (!file.is_open()) {
		std::cerr << "ChessBoard::load_pieces fail,file:" << path
				<< " open fail" << std::endl;
		return;
	}
	std::istream is(&file);
	std::string line;
	Piece* piece;
	while(Tim::String::get_line(is, line, true, true)&&line!="#END"){
		if(line=="piece_path:"){
			Tim::String::get_line(is, line, true, true);
			piece=new Piece();
			piece->load_script(dir_path,line);

			pieces.push_back(piece);
		}
	}
	file.close();
	init_pieces();
}
void ChessBoard::save_mct(){
	if(!mct)return;
	mct->save(dir_path+"chessBoard/boardMCT.txt");
}
void ChessBoard::load_mct(){
	if(mct)delete mct;
	mct = new BoardMCT();
	mct->load(dir_path+"chessBoard/boardMCT.txt");
	cur_node=mct->step_root;
	std::cout<<"ChessBoard::load_mct()"<<
			"total simulations:"<<mct->step_root->data.simulations<<
			",total wins:"<<mct->step_root->data.wins<<std::endl;
}
void ChessBoard::save_board(std::string path){
	FILE * file = fopen(path.c_str(),"w+t");
	fprintf(file,"%d %d %d\n",board->sizex,board->sizey,board->sizez);
	int type;
	for(int j=0;j<board->sizey;j++){
		for(int i=0;i<board->sizex;i++){
			for(int k=0;k<board->sizez;k++){
				type=board->get(i,j,k);
				fprintf(file,"%3d ",type);
			}
			fprintf(file,"\n");
		}
		fprintf(file,"\n");
	}
	for(int i=0;i<chess_board->sizex;i++){
			for(int j=0;j<chess_board->sizey;j++){
				type=chess_board->get(i,j);
				//fprintf(file,"%d\n",type);
				fprintf(file,"%3d ",type);
			}
			fprintf(file,"\n");
	}
	fclose(file);
}
void ChessBoard::load_board(std::string path){

	FILE * file = fopen(path.c_str(),"r");
	int sizex,sizey,sizez;
	fscanf(file,"%d %d %d\n",&sizex,&sizey,&sizez);
	size.x=sizex;
	size.y=sizey;
	size.z=sizez;
	init_board();
	int type;
	for(int j=0;j<board->sizey;j++){
		for(int i=0;i<board->sizex;i++){
			for(int k=0;k<board->sizez;k++){
				fscanf(file,"%d",&type);
				board->get(i,j,k)=type;
			}
		}
	}
	for(int i=0;i<chess_board->sizex;i++){
			for(int j=0;j<chess_board->sizey;j++){
				fscanf(file,"%d",&type);
				chess_board->get(i,j)=type;
				if(type>0){
					chess_board->piece_num[type-1]++;
				}else if(type<0){
					chess_board->piece_num[-type-1]--;
				}

			}
	}
	fclose(file);
	updated=true;
}
void ChessBoard::gen_model(){
	//Model *mapmodel = dmaps[px][pz]->model;
	static const unsigned char up = 1 << 0;
	static const unsigned char down = 1 << 1;
	static const unsigned char left = 1 << 2;
	static const unsigned char right = 1 << 3;
	static const unsigned char front = 1 << 4;
	static const unsigned char back = 1 << 5;
	unsigned char cube_exist;
	int tex_layer;
	Display::Model *model = dboard->model;
	model->clear();
	for (int i = 0; i < board->sizex; i++) {
		for (int j = 0; j < board->sizey; j++) {
			for (int k = 0; k < board->sizez; k++) {
				int type = board->get(i, j, k);

				if (type > 0) {
					tex_layer = type-1;
					cube_exist = 0;
					glm::vec3 pos = glm::vec3((i + 0.5) * cube_size,
							(j + 0.5) * cube_size,
							(k + 0.5) * cube_size);

					if (get_type(i, j + 1, k) > 0)
						cube_exist |= up;
					if (get_type(i, j - 1, k) > 0)
						cube_exist |= down;
					if (get_type(i + 1, j, k) >0)
						cube_exist |= left;
					if (get_type(i - 1, j, k) >0)
						cube_exist |= right;
					if (get_type(i, j, k + 1) >0)
						cube_exist |= front;
					if (get_type(i, j, k - 1) >0)
						cube_exist |= back;


					if (!(cube_exist & up)) {
						model->merge(cube->cube[0], pos, tex_layer);
					}

					if (j - 1 < 0 ||!(cube_exist & down)) {
						model->merge(cube->cube[1], pos, tex_layer);
					}

					if (i + 1 >= board->sizex ||!(cube_exist & left)) {
						model->merge(cube->cube[2], pos, tex_layer);
					}

					if (i - 1 < 0 ||!(cube_exist & right)) {
						model->merge(cube->cube[3], pos, tex_layer);
					}

					if (k + 1 >= board->sizez ||!(cube_exist & front)) {
						model->merge(cube->cube[4], pos, tex_layer);
					}

					if (k - 1 < 0 ||!(cube_exist & back)) {
						model->merge(cube->cube[5], pos, tex_layer);
					}
				}
			}
		}
	}
	dboard->update_model();
	updated = false;
}
void ChessBoard::find_selected_on(glm::vec3 pos){
	const unsigned char left=1;
	const unsigned char right=2;
	const unsigned char front=3;
	const unsigned char back=4;
	const unsigned char up=5;
	const unsigned char down=6;
	float min_val=1.0,val;
	unsigned char dir=0;

	val=pos.y-floor(pos.y);
	if(val<0.5){
		if(val<min_val){
			if(get_type((int)pos.x,(int)pos.y-1,(int)pos.z)==0){
				min_val=val;
				dir=down;
			}
		}
	}else{
		if((1.0-val)<min_val){
			if(get_type((int)pos.x,(int)pos.y+1,(int)pos.z)==0){
				min_val=(1.0-val);
				dir=up;
			}
		}
	}

	val=pos.x-floor(pos.x);
	if(val<0.5){
		if(val<min_val){
			if(get_type((int)pos.x-1,(int)pos.y,(int)pos.z)==0){
				min_val=val;
				dir=left;
			}
		}
	}else{
		if((1.0-val)<min_val){
			if(get_type((int)pos.x+1,(int)pos.y,(int)pos.z)==0){
				min_val=(1.0-val);
				dir=right;
			}
		}
	}
	val=pos.z-floor(pos.z);
	if(val<0.5){
		if(val<min_val){
			if(get_type((int)pos.x,(int)pos.y,(int)pos.z-1)<=0){
				min_val=val;
				dir=back;
			}
		}
	}else{
		if((1.0-val)<min_val){
			if(get_type((int)pos.x,(int)pos.y,(int)pos.z+1)<=0){
				min_val=(1.0-val);
				dir=front;
			}
		}
	}
	if(dir==down){
		selected_on=glm::ivec3(pos.x,pos.y-1,pos.z);
	}else if(dir==up){
		selected_on=glm::ivec3(pos.x,pos.y+1,pos.z);
	}else if(dir==left){
		selected_on=glm::ivec3(pos.x-1,pos.y,pos.z);
	}else if(dir==right){
		selected_on=glm::ivec3(pos.x+1,pos.y,pos.z);
	}else if(dir==back){
		selected_on=glm::ivec3(pos.x,pos.y,pos.z-1);
	}else if(dir==front){
		selected_on=glm::ivec3(pos.x,pos.y,pos.z+1);
	}else{
		selected_on=glm::ivec3(-1,-1,-1);
	}
}
void ChessBoard::find_selected_cube(glm::vec3 pos){
	const unsigned char left=1;
	const unsigned char right=2;
	const unsigned char front=3;
	const unsigned char back=4;
	const unsigned char up=5;
	const unsigned char down=6;

	float min_val=1.0,val;
	unsigned char dir=0;
	val=pos.y-floor(pos.y);
	if(val<0.5){
		if(val<min_val){
			if((int)pos.y-1>=0&&
					get_type((int)pos.x,(int)pos.y-1,(int)pos.z)>0){
				min_val=val;
				dir=down;
			}
		}
	}else{
		if((1.0-val)<min_val){
			if((int)pos.y+1<board->sizey&&
					get_type((int)pos.x,(int)pos.y+1,(int)pos.z)>0){
				min_val=(1.0-val);
				dir=up;
			}
		}
	}

	val=pos.x-floor(pos.x);
	if(val<0.5){
		if(val<min_val){
			if((int)pos.y<board->sizey&&
					get_type((int)pos.x-1,(int)pos.y,(int)pos.z)>0){
				min_val=val;
				dir=left;
			}
		}
	}else{
		if((1.0-val)<min_val){
			if((int)pos.y<board->sizey&&
					get_type((int)pos.x+1,(int)pos.y,(int)pos.z)>0){
				min_val=(1.0-val);
				dir=right;
			}
		}
	}
	val=pos.z-floor(pos.z);
	if(val<0.5){
		if(val<min_val){
			if((int)pos.y<board->sizey&&
					get_type((int)pos.x,(int)pos.y,(int)pos.z-1)>0){
				min_val=val;
				dir=back;
			}
		}
	}else{
		if((1.0-val)<min_val){
			if((int)pos.y<board->sizey&&
					get_type((int)pos.x,(int)pos.y,(int)pos.z+1)>0){
				min_val=(1.0-val);
				dir=front;
			}
		}
	}
	if(dir==down){
		selected_cube=glm::ivec3(pos.x,pos.y-1,pos.z);
	}else if(dir==up){
		selected_cube=glm::ivec3(pos.x,pos.y+1,pos.z);
	}else if(dir==left){
		selected_cube=glm::ivec3(pos.x-1,pos.y,pos.z);
	}else if(dir==right){
		selected_cube=glm::ivec3(pos.x+1,pos.y,pos.z);
	}else if(dir==back){
		selected_cube=glm::ivec3(pos.x,pos.y,pos.z-1);
	}else if(dir==front){
		selected_cube=glm::ivec3(pos.x,pos.y,pos.z+1);
	}else{
		selected_on=glm::ivec3(-1,-1,-1);
	}
}
void ChessBoard::find_select_cube(){
	glm::vec3 pos=Input::Input::get_cur_object()->mouse->world_pos;
	pos=glm::vec3((pos.x/cube_size),
			      (pos.y/cube_size),
			      (pos.z/cube_size));
	glm::ivec3 p=glm::ivec3(pos.x,pos.y,pos.z);
	if(p.x>=0&&p.z>=0&&p.x<chess_board->sizex&&p.z<chess_board->sizey){
		selected_piece=glm::ivec2(p.x,p.z);
	}
	if(get_type(p.x,p.y,p.z)>0){//can be selected
		//std::cout<<"1"<<std::endl;
		selected_cube=p;
		find_selected_on(pos);
	}else{
		//std::cout<<"2"<<std::endl;
		selected_on=p;
		find_selected_cube(pos);
	}
}
void ChessBoard::move(Step &step){
	step.move(chess_board);
	cur_node=mct->find_and_expand(cur_node,step);
}
void ChessBoard::undo(Step &step){
	step.undo(chess_board);
	cur_node=(CM::StepNode*)cur_node->parent;
	winner=check_winner(chess_board);
}
void ChessBoard::undo(){
	if(steps.size()>=2){
		undo(*steps.back());
		delete steps.back();
		steps.pop_back();

		undo(*steps.back());
		delete steps.back();
		steps.pop_back();
	}
}
void ChessBoard::backpropagation(){
	bool win_node=true;
	for(CM::StepNode *node=cur_node;node!=0;node=(CM::StepNode *)node->parent){
		node->data.simulations++;
		if(win_node)node->data.wins++;

		win_node^=1;
	}
}
void ChessBoard::draw_backpropagation(){
	for(CM::StepNode *node=cur_node;node!=0;node=(CM::StepNode *)node->parent){
		node->data.simulations++;
	}
}
void ChessBoard::prev_turn(){
	if(steps.empty())return;
	undo(*steps.back());
	delete steps.back();
	steps.pop_back();
	cur_player*=-1;
}
void ChessBoard::next_turn(CM::Step step){
	steps.push_back(new CM::Step(&step));
	move(*steps.back());
	winner=check_winner(chess_board);
	if(winner!=0){
		backpropagation();
	}
	cur_player*=-1;
}
void ChessBoard::clear_steps(){
	for(unsigned i=0;i<steps.size();i++){
		delete steps.at(i);
	}
	steps.clear();
}
void ChessBoard::restart(){
	//winner=0;
	//cur_player=1;
	while(!steps.empty()){
		prev_turn();
		//undo(*steps.back());
		//delete steps.back();
		//steps.pop_back();
	}
}

void ChessBoard::draw(){
	//std::cout<<"ChessBoard::draw()"<<std::endl;
	if(updated)gen_model();
	dboard->draw=true;
	dboard->push_temp_drawdata(new Display::DrawDataObj(pos,true));
	int type;
	Position* pos;
	for(int i=0;i<chess_board->sizex;i++){
		for(int j=0;j<chess_board->sizey;j++){
			type=chess_board->get(i,j);
			if(type!=0){
				pos=new Position(glm::vec3((i+0.5f)*cube_size,
						  (2.5f)*cube_size,
						  (j+0.5f)*cube_size));
				if(type>0){
					pos->set_ry(180.0f);
					pieces.at(type-1)->draw(pos,1);
				}else{//P2
					pieces.at((-type)-1)->draw(pos,-1);

				}

			}
		}
	}
}
} /* namespace CM */
