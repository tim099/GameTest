#include "class/game/chessMaster/piece/Step.h"
#include "class/game/chessMaster/chessboard/ChessBoard.h"
#include "class/display/draw/Draw.h"
#include "class/display/light/LightControl.h"
#include <iostream>
namespace CM {

Step::Step() {
	score=0;
	moves.reserve(2);
}
Step::Step(Step *step){
	init(*step);
}
void Step::init(const Step &step){
	//std::cout<<"Step::init"<<std::endl;
	score=step.score;
	moves.clear();
	unsigned move_size=step.moves.size();
	moves.reserve(move_size);
	for(unsigned i=0;i<move_size;i++){
		moves.push_back(step.moves[i]);
	}
}
Step::~Step() {
	//std::cout<<"Step::~Step()"<<std::endl;
}
void Step::save(FILE * file){
	fprintf(file,"%d\n",score);
	fprintf(file,"%u\n",moves.size());
	Math::vec4<int> *move;
	for(unsigned i=0;i<moves.size();i++){
		move=&moves.at(i);
		fprintf(file,"%d,%d,%d,%d\n",move->x,move->y,move->z,move->w);
	}
}
void Step::load(FILE * file){
	fscanf(file,"%d\n",&score);
	unsigned move_size;
	fscanf(file,"%u\n",&move_size);
	Math::vec4<int> move;
	for(unsigned i=0;i<move_size;i++){
		fscanf(file,"%d,%d,%d,%d\n",&move.x,&move.y,&move.z,&move.w);
		moves.push_back(move);
	}
}
Step& Step::operator=(const Step& step){
	//std::cout<<"Step::operator="<<std::endl;
	init(step);
	return (*this);
}
bool Step::operator==(const Step& step){
	if(step.moves.size()!=moves.size()){
		return false;
	}
	for(unsigned i=0;i<moves.size();i++){
		if(step.moves.at(i).x!=moves.at(i).x||
				step.moves.at(i).y!=moves.at(i).y||
				step.moves.at(i).z!=moves.at(i).z){
			return false;
		}
	}
	return true;
}
bool Step::operator>(const Step& step){
	if(step.moves.size()>moves.size()){
		return false;
	}else if(step.moves.size()<moves.size()){
		return true;
	}
	//size equal
	for(unsigned i=0;i<moves.size();i++){
		if(step.moves.at(i).x>moves.at(i).x){
			return false;
		}else if(step.moves.at(i).x<moves.at(i).x){
			return true;
		}else{
			if(step.moves.at(i).y>moves.at(i).y){
				return false;
			}else if(step.moves.at(i).y<moves.at(i).y){
				return true;
			}else{
				if(step.moves.at(i).z>moves.at(i).z){
					return false;
				}else if(step.moves.at(i).z<moves.at(i).z){
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
	for(unsigned i=0;i<moves.size();i++){
		if(moves.at(i).z!=0&&moves.at(i).w!=-1){
			if(moves.at(i).x==x&&moves.at(i).y==y){
				return true;
			}
		}
	}
	return false;
}
void Step::draw_next_step(){
	ChessBoard* chess_board=ChessBoard::get_cur_object();
	Display::CubeLight* cl;
	for(unsigned i=0;i<moves.size();i++){
		if(selected(moves.at(i).x,moves.at(i).y)){
			cl=new Display::CubeLight();
			cl->size=1.01f*chess_board->cube_size;
			if(moves.at(i).z*chess_board->get_type(moves.at(i).x,moves.at(i).y)<0){
				cl->color=glm::vec3(0.5,0,0);
			}else{
				cl->color=glm::vec3(0,0.5,0);
			}
			cl->pos=glm::vec3((moves.at(i).x+0.5f)*chess_board->cube_size,
							  (2.5f)*chess_board->cube_size,
							  (moves.at(i).y+0.5f)*chess_board->cube_size);
			//chess_board->get_piece(x,y)->draw()
			Display::Draw::get_cur_object()->lightControl->push_temp_light(cl);
		}
	}
}
void Step::draw_step(glm::vec3 color){
	ChessBoard* chess_board=ChessBoard::get_cur_object();
	Display::CubeLight* cl;
	for(unsigned i=0;i<moves.size();i++){
		cl=new Display::CubeLight();
		cl->size=1.01f*chess_board->cube_size;
		cl->color=color;
		cl->pos=glm::vec3((moves.at(i).x+0.5f)*chess_board->cube_size,
						  (2.5f)*chess_board->cube_size,
						  (moves.at(i).y+0.5f)*chess_board->cube_size);
		Display::Draw::get_cur_object()->lightControl->push_temp_light(cl);
	}
}
} /* namespace CM */
