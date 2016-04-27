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
	void move(Tim::Array2D<short int> *chess_board);
	void undo(Tim::Array2D<short int> *chess_board);
	void draw_next_step();
	void draw_step(glm::vec3 color);

	bool selected(int x,int y);//return true if x,y selected on this step
	inline void parse_step(Tim::Array2D<short int> *chess_board,int x,int y,
			std::vector<int> &next_step,int &i){
		moves.clear();
		moves.reserve(2);
		if(next_step[i]>=0){
			moves.push_back(Math::vec4<int>(x,y,0,-1));
			moves.push_back(Math::vec4<int>(next_step[i],next_step[i+1],chess_board->get(x,y),1));
			i+=2;
		}else if(next_step[i]==-1){
			int move_num=next_step[i+1];
			while(move_num>0){
				i+=2;
				moves.push_back(Math::vec4<int>(next_step[i],next_step[i+1],
						next_step[i+2],next_step[i+3]));
				i+=2;
				move_num--;
			}
			i+=2;
		}
	}
	int score;
	std::vector<Math::vec4<int> > moves;
protected:

};

} /* namespace CM */

#endif /* SOURCE_CLASS_GAME_CHESSMASTER_PIECE_STEP_H_ */
