#ifndef SOURCE_CLASS_GAME_CHESSMASTER_PIECE_STEP_H_
#define SOURCE_CLASS_GAME_CHESSMASTER_PIECE_STEP_H_
#include "class/game/chessMaster/chessboard/Board.h"
#include <vector>
#include <cstdio>

#include "class/tim/math/vec4.h"
#include <algorithm>
namespace CM {

class Step {
	static const int max_move=8;
public:
	Step();
	Step(Step *step);
	inline void init(const Step &step){
		score=step.score;
		move_num=step.move_num;
		std::copy(step.moves,step.moves+move_num,moves);
	}
	virtual ~Step();


	void save(FILE * file);
	void load(FILE * file);

	inline Step& operator=(const Step& step){
		//init(step);
		score=step.score;
		move_num=step.move_num;
		std::copy(step.moves,step.moves+move_num,moves);
		return (*this);
	}
	inline bool operator==(const Step& step){
		if(step.move_num!=move_num){
			return false;
		}
		for(unsigned i=0;i<move_num;i++){
			if(step.moves[i].x!=moves[i].x||
					step.moves[i].y!=moves[i].y||
					step.moves[i].z!=moves[i].z){
				return false;
			}
		}
		return true;
	}
	bool operator>(const Step& step);
	bool operator<(const Step& step);
	inline void add_move(const int &x,const int &y,const int &z,const int &w){
		moves[move_num].x=x;moves[move_num].y=y;moves[move_num].z=z;moves[move_num].w=w;
		move_num++;
	}
	inline void move(CM::Board<short int> *chess_board){
		for(unsigned i=0;i<move_num;i++){
			moves[i].w=chess_board->get(moves[i].x,moves[i].y);
			chess_board->get(moves[i].x,moves[i].y)=moves[i].z;

			if(moves[i].z>0){
				chess_board->piece_num[moves[i].z-1]++;
			}else if(moves[i].z<0){
				chess_board->piece_num[-moves[i].z-1]--;
			}
			if(moves[i].w>0){
				chess_board->piece_num[moves[i].w-1]--;
			}else if(moves[i].w<0){
				chess_board->piece_num[-moves[i].w-1]++;
			}

		}
	}
	inline void undo(CM::Board<short int> *chess_board){
		for(unsigned i=0;i<move_num;i++){
			if(moves[i].z>0){
				chess_board->piece_num[moves[i].z-1]--;
			}else if(moves[i].z<0){
				chess_board->piece_num[-moves[i].z-1]++;
			}
			if(moves[i].w>0){
				chess_board->piece_num[moves[i].w-1]++;
			}else if(moves[i].w<0){
				chess_board->piece_num[-moves[i].w-1]--;
			}
			chess_board->get(moves[i].x,moves[i].y)=moves[i].w;
		}
	}
	void draw_next_step();
	void draw_step(float r,float g,float b);

	bool selected(int x,int y);//return true if x,y selected on this step
	inline void parse_step(Tim::Array2D<short int> *chess_board,int x,int y,
			std::vector<int> &next_step,int &i){
		move_num=0;
		if(next_step[i]>=0){
			//moves[move_num++]=Math::vec4<int>(x,y,0,-1);
			add_move(x,y,0,-1);
			moves[move_num++]=math::vec4<short int>(next_step[i],next_step[i+1],chess_board->get(x,y),1);
			i+=2;
		}else if(next_step[i]==-1){
			int total_move_num=next_step[i+1];
			while(total_move_num>0){
				i+=2;
				moves[move_num++]=(math::vec4<short int>(next_step[i],next_step[i+1],
						next_step[i+2],next_step[i+3]));
				i+=2;
				total_move_num--;
			}
			i+=2;
		}
	}
	int score;
	math::vec4<short int> moves[max_move];
	unsigned move_num;
protected:

};

} /* namespace CM */

#endif /* SOURCE_CLASS_GAME_CHESSMASTER_PIECE_STEP_H_ */
