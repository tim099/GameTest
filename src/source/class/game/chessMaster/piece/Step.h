#ifndef SOURCE_CLASS_GAME_CHESSMASTER_PIECE_STEP_H_
#define SOURCE_CLASS_GAME_CHESSMASTER_PIECE_STEP_H_
#include "class/tim/array/Array2D.h"
#include <vector>
#include <cstdio>
#include <glm/vec3.hpp>
#include <glm/vec2.hpp>
#include "class/tim/math/vec4.h"
namespace CM {

class Step {
	static const int max_move=10;
public:
	Step();
	Step(Step *step);
	void init(const Step &step);
	virtual ~Step();


	void save(FILE * file);
	void load(FILE * file);

	Step& operator=(const Step& step);
	bool operator==(const Step& step);
	bool operator>(const Step& step);
	bool operator<(const Step& step);
	inline void add_move(const int &x,const int &y,const int &z,const int &w){
		moves[move_num].x=x;moves[move_num].y=y;moves[move_num].z=z;moves[move_num].w=w;
		move_num++;
	}
	inline void move(Tim::Array2D<short int> *chess_board){
		for(unsigned i=0;i<move_num;i++){
			moves[i].w=chess_board->get(moves[i].x,moves[i].y);
			chess_board->get(moves[i].x,moves[i].y)=moves[i].z;
		}
	}
	inline void undo(Tim::Array2D<short int> *chess_board){
		for(unsigned i=0;i<move_num;i++){
			chess_board->get(moves[i].x,moves[i].y)=moves[i].w;
		}
	}
	void draw_next_step();
	void draw_step(glm::vec3 color);

	bool selected(int x,int y);//return true if x,y selected on this step
	inline void parse_step(Tim::Array2D<short int> *chess_board,int x,int y,
			std::vector<int> &next_step,int &i){
		move_num=0;
		if(next_step[i]>=0){
			//moves[move_num++]=Math::vec4<int>(x,y,0,-1);
			add_move(x,y,0,-1);
			moves[move_num++]=Math::vec4<int>(next_step[i],next_step[i+1],chess_board->get(x,y),1);
			i+=2;
		}else if(next_step[i]==-1){
			int total_move_num=next_step[i+1];
			while(total_move_num>0){
				i+=2;
				moves[move_num++]=(Math::vec4<int>(next_step[i],next_step[i+1],
						next_step[i+2],next_step[i+3]));
				i+=2;
				total_move_num--;
			}
			i+=2;
		}
	}
	int score;
	Math::vec4<int> moves[max_move];
	unsigned move_num;
protected:

};

} /* namespace CM */

#endif /* SOURCE_CLASS_GAME_CHESSMASTER_PIECE_STEP_H_ */
