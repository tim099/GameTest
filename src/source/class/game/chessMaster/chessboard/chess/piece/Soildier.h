#ifndef SOURCE_CLASS_GAME_CHESSMASTER_CHESSBOARD_CHESS_PIECE_SOILDIER_H_
#define SOURCE_CLASS_GAME_CHESSMASTER_CHESSBOARD_CHESS_PIECE_SOILDIER_H_
#include "class/game/chessMaster/piece/Piece.h"
namespace CM {

class Soildier : public Piece{
public:
	Soildier();
	virtual ~Soildier();
	inline bool bound_check(int x,int y){
		if(x>=0&&y>=0&&x<=8&&y<=9){
			return true;
		}
		return false;
	}
	virtual void next_step(Tim::Array2D<short int> *chess_board,
			int x,int y,std::vector<CM::Step> &next_step,int player);
};

} /* namespace CM */

#endif /* SOURCE_CLASS_GAME_CHESSMASTER_CHESSBOARD_CHESS_PIECE_SOILDIER_H_ */
