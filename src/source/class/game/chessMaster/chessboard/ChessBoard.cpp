#include "class/game/chessMaster/chessboard/ChessBoard.h"
#include "class/display/draw/Draw.h"
#include "class/display/draw/drawObject/drawData/DrawDataObj.h"
#include "class/input/Input.h"
#include "class/tim/string/String.h"

#include <fstream>
#include <iostream>
#include <cmath>
namespace CM {
ChessBoard::ChessBoard(int sizex,int sizey,int sizez) {
	cube_size=1.0;
	board=0;
	chess_board=0;
	cur_board=0;
	board_mutex=new Tim::Mutex();
	rule=0;
	cube_type_num=3;
	dboard = new DynamicDrawObject();
	tex_path="chess/board_textures";
	normal_path="chess/board_normals";
	dboard->init_drawObject("",tex_path,normal_path,true);
	Draw::get_cur_object()->push(dboard);

	pos = new Position(glm::vec3(0, 0, 0), glm::vec3());
	cube = new CubeModel(0.5*cube_size);

	init(sizex,sizey,sizez);

	register_cur();
}
ChessBoard::~ChessBoard() {
	for(unsigned i=0;i<pieces.size();i++)delete pieces.at(i);
	if(board)delete board;
	if(chess_board)delete chess_board;
	if(rule)delete rule;
	delete board_mutex;
	clear_steps();
	delete dboard;
	delete pos;
	delete cube;
}
void ChessBoard::clear(){
	for(unsigned i=0;i<pieces.size();i++)delete pieces.at(i);
	pieces.clear();
	clear_steps();
}
void ChessBoard::init(int sizex,int sizey,int sizez){
	if(board)delete board;
	if(chess_board)delete chess_board;
	board=new Tim::Array3D<unsigned char>(sizex,sizey,sizez);
	chess_board=new Tim::Array2D<short int>(sizex,sizez);
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
	for(int i=0;i<chess_board->sizex;i++){
		for(int j=0;j<chess_board->sizey;j++){
			chess_board->get(i,j)=0;
		}
	}
	updated=true;
}
int ChessBoard::get_board(lua_State *L){
	//std::cout<<"ChessBoard::get_board"<<std::endl;

	lua_getglobal(L, "board");
	Tim::Array2D<short int> *cb =(Tim::Array2D<short int>*)lua_touserdata(L,-1);
	lua_pop(L,1);
	//Tim::Array2D<short int> *cb=ChessBoard::get_cur_object()->cur_board;

	int y = lua_tonumber(L, -1);
	lua_pop(L,1);
	int x = lua_tonumber(L, -1);
	lua_pop(L,1);


	int type=cb->get(x,y);;

	lua_pushnumber(L,type);

	return 1;
}
int ChessBoard::check_winner(Tim::Array2D<short int> *cb){
	int result=rule->check_winner(cb);
	return result;
}
int ChessBoard::evaluate_score(Tim::Array2D<short int> *cb,int player){
	int total_score=0;
	int type,weight;
	for(int i=0;i<cb->sizex;i++){
		for(int j=0;j<cb->sizey;j++){
			type=cb->get(i,j);
			if(type!=0){
				weight=pieces.at(abs(type)-1)->weight;
				if(type*player>0){
					total_score+=weight;
				}else{
					total_score-=weight;
				}
			}
		}
	}
	return total_score;
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
	if(Tim::String::get_line(is, line, true, true)&&line=="board_path:"){
		Tim::String::get_line(is, line, true, true);
		load_board(line);
	}else{
		std::cerr << "ChessBoard::load_script fail,no board_path:" <<std::endl;
	}
	if(Tim::String::get_line(is, line, true, true)&&line=="pieces_path:"){
		Tim::String::get_line(is, line, true, true);
		load_pieces(line);
	}else{
		std::cerr << "ChessBoard::load_script fail,no pieces_path:" <<std::endl;
	}
	if(Tim::String::get_line(is, line, true, true)&&line=="rule_path:"){
		Tim::String::get_line(is, rule_path, true, true);
	}

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
	rule->load_rule(rule_path);
	file.close();
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
			piece->load_script(line);

			pieces.push_back(piece);
		}
	}
	file.close();
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
	for(int i=0;i<board->sizex;i++){
			for(int k=0;k<board->sizez;k++){
				type=chess_board->get(i,k);
				//fprintf(file,"%d\n",type);
				fprintf(file,"%3d ",type);
			}
			fprintf(file,"\n");
	}
	fclose(file);
}
void ChessBoard::load_board(std::string path){
	clear_steps();
	FILE * file = fopen(path.c_str(),"r");
	int sizex,sizey,sizez;
	fscanf(file,"%d %d %d\n",&sizex,&sizey,&sizez);

	init(sizex,sizey,sizez);
	int type;
	for(int j=0;j<board->sizey;j++){
		for(int i=0;i<board->sizex;i++){
			for(int k=0;k<board->sizez;k++){
				fscanf(file,"%d",&type);
				board->get(i,j,k)=type;
			}
		}
	}
	for(int i=0;i<board->sizex;i++){
			for(int k=0;k<board->sizez;k++){
				fscanf(file,"%d",&type);
				chess_board->get(i,k)=type;//;
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
	Model *model = dboard->model;
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
	glm::vec3 pos=Input::get_cur_object()->mouse->world_pos;
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
void ChessBoard::find_next_step(Tim::Array2D<short int> *cb,
		int player,std::vector<CM::Step> &next){
	next.clear();
	int type;
	for(int i=0;i<cb->sizex;i++){
		for(int j=0;j<cb->sizey;j++){
			type=cb->get(i,j);
			if(type*player>0){//player's chess
				find_next_step(cb,glm::ivec2(i,j),next);
			}
		}
	}
}
void ChessBoard::find_next_step(Tim::Array2D<short int> *cb,
		glm::ivec2 cur_step,std::vector<CM::Step> &next_steps){
	int type=cb->get(cur_step.x,cur_step.y);
	int player=1;
	if(type<0){
		type*=-1;
		player=-1;
	}
	type-=1;
	pieces.at(type)->next_step(cb,cur_step,next_steps,player);
}
void ChessBoard::move(Step &step){
	step.move(chess_board);
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
void ChessBoard::next_turn(CM::Step step){
	steps.push_back(new CM::Step(&step));
	move(*steps.back());
}
void ChessBoard::clear_steps(){
	for(unsigned i=0;i<steps.size();i++){
		delete steps.at(i);
	}
	steps.clear();
}
void ChessBoard::restart(){
	while(!steps.empty()){
		undo(*steps.back());
		delete steps.back();
		steps.pop_back();
	}
}
void ChessBoard::undo(Step &step){
	step.undo(chess_board);
}
void ChessBoard::draw(){
	//std::cout<<"ChessBoard::draw()"<<std::endl;
	if(updated)gen_model();
	dboard->draw=true;
	dboard->push_temp_drawdata(new DrawDataObj(pos,true));

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
