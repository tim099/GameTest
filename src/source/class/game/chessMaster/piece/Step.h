#ifndef SOURCE_CLASS_GAME_CHESSMASTER_PIECE_STEP_H_
#define SOURCE_CLASS_GAME_CHESSMASTER_PIECE_STEP_H_

namespace CM {

class Step {
public:
	Step(int x=0,int y=0,int nx=0,int ny=0,int score=0);
	Step(Step *step);
	Step& operator=(const Step& step);
	virtual ~Step();
	int x,y,nx,ny;
	int ntype;
	int score;
};

} /* namespace CM */

#endif /* SOURCE_CLASS_GAME_CHESSMASTER_PIECE_STEP_H_ */
