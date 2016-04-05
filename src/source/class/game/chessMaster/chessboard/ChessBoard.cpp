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
	dboard = new DynamicDrawObject();
	dboard->init_drawObject("","cube/cube_textures","cube/cube_normals",true);
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
	delete dboard;
	delete pos;
	delete cube;
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
int ChessBoard::evaluate_score(Tim::Array2D<short int> *chess_board,int player){
	int total_score=0;
	int type,weight;
	for(int i=0;i<chess_board->sizex;i++){
		for(int j=0;j<chess_board->sizey;j++){
			type=chess_board->get(i,j);
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
	if(x<0||y<0||x>=chess_board->sizex||y>chess_board->sizey){
		std::cerr<<"ChessBoard::get_type out of range"<<x<<","<<y<<std::endl;
		return 0;
	}
	return chess_board->get(x,y);
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
	for(int i=0;i<board->sizex;i++){
		for(int j=0;j<board->sizey;j++){
			for(int k=0;k<board->sizez;k++){
				type=board->get(i,j,k);
				fprintf(file,"%u\n",type);
			}
		}
	}
	for(int i=0;i<board->sizex;i++){
			for(int k=0;k<board->sizez;k++){
				type=chess_board->get(i,k);
				fprintf(file,"%d\n",type);
			}
	}
	fclose(file);
}
void ChessBoard::load_board(std::string path){
	FILE * file = fopen(path.c_str(),"r");
	int sizex,sizey,sizez;
	fscanf(file,"%d %d %d\n",&sizex,&sizey,&sizez);

	init(sizex,sizey,sizez);
	int type;
	for(int i=0;i<board->sizex;i++){
		for(int j=0;j<board->sizey;j++){
			for(int k=0;k<board->sizez;k++){
				fscanf(file,"%d",&type);
				board->get(i,j,k)=type;
			}
		}
	}
	for(int i=0;i<board->sizex;i++){
			for(int k=0;k<board->sizez;k++){
				fscanf(file,"%d\n",&type);
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
					tex_layer = type;
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
	selected_piece=glm::ivec2(p.x,p.z);
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
void ChessBoard::find_next_step(glm::ivec2 cur_step,std::vector<glm::ivec2> &next_step){
	int type=chess_board->get(cur_step.x,cur_step.y);
	next_step.clear();
	bool player1=true;
	if(type<0){
		type*=-1;
		player1=false;
	}
	type-=1;
	pieces.at(type)->next_step(cur_step,next_step,player1);
}
void ChessBoard::move(Step &step){
	int type=get_type(step.x,step.y);
	step.ntype=get_type(step.nx,step.ny);
	set_type(step.x,step.y,0);
	set_type(step.nx,step.ny,type);
}
void ChessBoard::undo(Step &step){
	int type=get_type(step.nx,step.ny);
	set_type(step.x,step.y,type);
	set_type(step.nx,step.ny,step.ntype);
}
void ChessBoard::draw(){
	//std::cout<<"ChessBoard::draw()"<<std::endl;
	if(updated)gen_model();
	dboard->draw=true;
	dboard->push_temp_drawdata(new DrawDataObj(pos,true));
	for(unsigned int i=0;i<pieces_pos.size();i++)delete pieces_pos.at(i);
	pieces_pos.clear();
	int type;
	Position* pos;
	for(int i=0;i<chess_board->sizex;i++){
		for(int j=0;j<chess_board->sizey;j++){
			type=chess_board->get(i,j);
			if(type!=0){
				pos=new Position(glm::vec3((i+0.5f)*cube_size,
						  (2.5f)*cube_size,
						  (j+0.5f)*cube_size));
				pieces_pos.push_back(pos);
				if(type>0){
					pos->set_ry(180.0f);
					pieces.at(type-1)->draw(pos,true);
				}else{//P2
					pieces.at((-type)-1)->draw(pos,false);

				}

			}
		}
	}
}
} /* namespace CM */
