#include "class/game/chessMaster/piece/Step.h"
#include "class/game/chessMaster/chessboard/ChessBoard.h"
#include "class/display/draw/Draw.h"
#include "class/display/light/LightControl.h"

namespace CM {

Step::Step() {
	score=0;
}
Step::Step(Step *step){
	init(*step);
}
void Step::init(const Step &step){
	score=step.score;
	moves.clear();
	for(unsigned i=0;i<step.moves.size();i++){
		moves.push_back(step.moves.at(i));
	}
}
Step::~Step() {

}
void Step::save(FILE * file){
	fprintf(file,"%d\n",score);
	fprintf(file,"%u\n",moves.size());
	glm::ivec4 *move;
	for(unsigned i=0;i<moves.size();i++){
		move=&moves.at(i);
		fprintf(file,"%d,%d,%d,%d\n",move->x,move->y,move->z,move->w);
	}
}
void Step::load(FILE * file){
	fscanf(file,"%d\n",&score);
	unsigned move_size;
	fscanf(file,"%u\n",&move_size);
	glm::ivec4 move;
	for(unsigned i=0;i<move_size;i++){
		fscanf(file,"%d,%d,%d,%d\n",&move.x,&move.y,&move.z,&move.w);
		moves.push_back(move);
	}
}
void Step::move(Tim::Array2D<short int> *chess_board){
	for(unsigned i=0;i<moves.size();i++){
		moves.at(i).w=chess_board->get(moves.at(i).x,moves.at(i).y);
		chess_board->get(moves.at(i).x,moves.at(i).y)=moves.at(i).z;
	}
}
void Step::undo(Tim::Array2D<short int> *chess_board){
	for(unsigned i=0;i<moves.size();i++){
		chess_board->get(moves.at(i).x,moves.at(i).y)=moves.at(i).w;
	}
}
void Step::parse_step(Tim::Array2D<short int> *chess_board,int x,int y,std::vector<int> &next_step,int &i){
	moves.clear();
	moves.reserve(2);
	if(next_step[i]>=0){
		moves.push_back(glm::ivec4(x,y,0,-1));
		moves.push_back(glm::ivec4(next_step[i],next_step[i+1],chess_board->get(x,y),1));
		i+=2;
	}else if(next_step[i]==-1){
		int move_num=next_step[i+1];
		while(move_num>0){
			i+=2;
			moves.push_back(glm::ivec4(next_step[i],next_step[i+1],
					next_step[i+2],next_step[i+3]));
			i+=2;
			move_num--;
		}
		i+=2;
	}
}
Step& Step::operator=(const Step& step){
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
	CubeLight* cl;
	for(unsigned i=0;i<moves.size();i++){
		if(selected(moves.at(i).x,moves.at(i).y)){
			cl=new CubeLight();
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
			Draw::get_cur_object()->lightControl->push_temp_light(cl);
		}
	}
}
void Step::draw_step(glm::vec3 color){
	ChessBoard* chess_board=ChessBoard::get_cur_object();
	CubeLight* cl;
	for(unsigned i=0;i<moves.size();i++){
		cl=new CubeLight();
		cl->size=1.01f*chess_board->cube_size;
		cl->color=color;
		cl->pos=glm::vec3((moves.at(i).x+0.5f)*chess_board->cube_size,
						  (2.5f)*chess_board->cube_size,
						  (moves.at(i).y+0.5f)*chess_board->cube_size);
		Draw::get_cur_object()->lightControl->push_temp_light(cl);
	}
}
} /* namespace CM */
