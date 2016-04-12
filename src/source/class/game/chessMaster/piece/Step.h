#ifndef SOURCE_CLASS_GAME_CHESSMASTER_PIECE_STEP_H_
#define SOURCE_CLASS_GAME_CHESSMASTER_PIECE_STEP_H_
#include "class/tim/array/Array2D.h"
#include <vector>
#include <glm/vec4.hpp>
#include <glm/vec3.hpp>
#include <glm/vec2.hpp>
namespace CM {

class Step {
public:
	Step();
	Step(Step *step);
	void init(const Step &step);
	virtual ~Step();
	Step& operator=(const Step& step);
	void move(Tim::Array2D<short int> *chess_board);
	void undo(Tim::Array2D<short int> *chess_board);
	void draw_next_step();
	void draw_step(glm::vec3 color);

	bool selected(int x,int y);//return true if x,y selected on this step
	void parse_step(Tim::Array2D<short int> *chess_board,glm::ivec2 cur_step,std::vector<int> &next_step,int &i);
	inline void add_move(int x,int y,int type,int selected){
		moves.push_back(glm::ivec4(x,y,type,selected));
	}
	int score;
protected:
	std::vector<glm::ivec4> moves;
};

} /* namespace CM */

#endif /* SOURCE_CLASS_GAME_CHESSMASTER_PIECE_STEP_H_ */
