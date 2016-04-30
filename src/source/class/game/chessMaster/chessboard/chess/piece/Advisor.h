#ifndef SOURCE_CLASS_GAME_CHESSMASTER_CHESSBOARD_CHESS_PIECE_ADVISOR_H_
#define SOURCE_CLASS_GAME_CHESSMASTER_CHESSBOARD_CHESS_PIECE_ADVISOR_H_

#include "class/game/chessMaster/piece/Piece.h"

namespace CM {

class Advisor: public Piece {
public:
	Advisor();
	virtual ~Advisor();
	inline bool in_nine(int x,int y){
		if((x>=3)&&(x<=5)){
			if(((y>=0)&&(y<=2))||((y>=7)&&(y<=9))){
				return true;
			}
		}
		return false;
	}
	inline bool bound_check(int x,int y){
		if(x>=0&&y>=0&&x<=8&&y<=9){
			return true;
		}
		return false;
	}
	virtual void next_step(Tim::Array2D<short int> *chess_board,
			int x,int y,Tim::vector<CM::Step> &next_step,int player);
};

} /* namespace CM */

#endif /* SOURCE_CLASS_GAME_CHESSMASTER_CHESSBOARD_CHESS_PIECE_ADVISOR_H_ */
