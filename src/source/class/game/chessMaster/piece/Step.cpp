#include "class/game/chessMaster/piece/Step.h"
#include "class/game/chessMaster/chessboard/ChessBoard.h"
#include "class/display/draw/Draw.h"
#include "class/display/light/LightControl.h"
#include <glm/vec3.hpp>
#include <iostream>
namespace CM {

Step::Step() {
	score=0;
	move_num=0;
}
Step::Step(Step *step){
	init(*step);
}
Step::~Step() {
	//std::cout<<"Step::~Step()"<<std::endl;
}
void Step::save(FILE * file){
	fprintf(file,"%d\n",score);
	fprintf(file,"%u\n",move_num);
	math::vec4<short int> *move;
	for(unsigned i=0;i<move_num;i++){
		move=&moves[i];
		fprintf(file,"%d,%d,%d,%d\n",move->x,move->y,move->z,move->w);
	}
}
void Step::load(FILE * file){
	fscanf(file,"%d\n",&score);
	fscanf(file,"%u\n",&move_num);
	int x,y,z,w;
	for(unsigned i=0;i<move_num;i++){
		fscanf(file,"%d,%d,%d,%d\n",&x,&y,&z,&w);
		moves[i].x=x;moves[i].y=y;moves[i].z=z;moves[i].w=w;
	}
}
bool Step::operator>(const Step& step){
	if(step.move_num>move_num){
		return false;
	}else if(step.move_num<move_num){
		return true;
	}
	//size equal
	for(unsigned i=0;i<move_num;i++){
		if(step.moves[i].x>moves[i].x){
			return false;
		}else if(step.moves[i].x<moves[i].x){
			return true;
		}else{
			if(step.moves[i].y>moves[i].y){
				return false;
			}else if(step.moves[i].y<moves[i].y){
				return true;
			}else{
				if(step.moves[i].z>moves[i].z){
					return false;
				}else if(step.moves[i].z<moves[i].z){
					return true;
				}
			}
		}

	}
	return false;
}
bool Step::operator<(const Step& step){
	if((*this)==step||((*this)>step))return false;
	return true;
}
bool Step::selected(int x,int y){
	for(unsigned i=0;i<move_num;i++){
		if(moves[i].z!=0&&moves[i].w!=-1){
			if(moves[i].x==x&&moves[i].y==y){
				return true;
			}
		}
	}
	return false;
}
void Step::draw_next_step(){
	ChessBoard* chess_board=ChessBoard::get_cur_object();
	Display::CubeLight* cl;
	for(unsigned i=0;i<move_num;i++){
		if(selected(moves[i].x,moves[i].y)){
			cl=new Display::CubeLight();
			cl->size=1.01f*chess_board->cube_size;
			if(moves[i].z*chess_board->get_type(moves[i].x,moves[i].y)<0){
				cl->color=glm::vec3(0.5,0,0);
			}else{
				cl->color=glm::vec3(0,0.5,0);
			}
			cl->pos=glm::vec3((moves[i].x+0.5f)*chess_board->cube_size,
							  (2.5f)*chess_board->cube_size,
							  (moves[i].y+0.5f)*chess_board->cube_size);
			Display::Draw::get_cur_object()->lightControl->push_temp_light(cl);
		}
	}
}
void Step::draw_step(float r,float g,float b){
	ChessBoard* chess_board=ChessBoard::get_cur_object();
	Display::CubeLight* cl;
	for(unsigned i=0;i<move_num;i++){
		cl=new Display::CubeLight();
		cl->size=1.01f*chess_board->cube_size;
		cl->color=glm::vec3(r,g,b);
		cl->pos=glm::vec3((moves[i].x+0.5f)*chess_board->cube_size,
						  (2.5f)*chess_board->cube_size,
						  (moves[i].y+0.5f)*chess_board->cube_size);
		Display::Draw::get_cur_object()->lightControl->push_temp_light(cl);
	}
}
} /* namespace CM */
