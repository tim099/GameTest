#ifndef SOURCE_CLASS_GAME_CHESSMASTER_CHESSBOARD_CHESS_PIECE_CANNON_H_
#define SOURCE_CLASS_GAME_CHESSMASTER_CHESSBOARD_CHESS_PIECE_CANNON_H_
#include "class/game/chessMaster/piece/Piece.h"
namespace CM {

class Cannon : public Piece{
public:
	Cannon();
	virtual ~Cannon();
	inline bool bound_check(int x,int y){
		if(x>=0&&y>=0&&x<=8&&y<=9){
			return true;
		}
		return false;
	}
	void cannon_move(Tim::Array2D<short int> *chess_board,
			int x,int y,int dx,int dy,int player
			,std::vector<int> &next_step);
	virtual void next_step(Tim::Array2D<short int> *chess_board,
			int x,int y,std::vector<int> &next_step,int player);
};

} /* namespace CM */

#endif /* SOURCE_CLASS_GAME_CHESSMASTER_CHESSBOARD_CHESS_PIECE_CANNON_H_ */
