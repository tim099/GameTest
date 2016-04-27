#ifndef SOURCE_CLASS_GAME_CHESSMASTER_CHESSBOARD_CHESS_PIECE_CHARIOT_H_
#define SOURCE_CLASS_GAME_CHESSMASTER_CHESSBOARD_CHESS_PIECE_CHARIOT_H_
#include "class/game/chessMaster/piece/Piece.h"
namespace CM {

class Chariot : public Piece{
public:
	Chariot();
	virtual ~Chariot();
	inline bool bound_check(int x,int y){
		if(x>=0&&y>=0&&x<=8&&y<=9){
			return true;
		}
		return false;
	}
	inline void move_straight(Tim::Array2D<short int> *chess_board,
			int x,int y,int dx,int dy,int player
			,std::vector<int> &next_step){
		int i=x+dx;
		int j=y+dy*player;
		int type;
		while(bound_check(i,j)){
			type=chess_board->get(i,j);
			if (type*player>0)break;//stop by player's own piece
			next_step.push_back(i);
			next_step.push_back(j);
			if (type*player<0)break;//attack enemy and stop here
			i+=dx;
			j+=dy*player;
		}
	}
	virtual void next_step(Tim::Array2D<short int> *chess_board,
			int x,int y,std::vector<int> &next_step,int player);
};

} /* namespace CM */

#endif /* SOURCE_CLASS_GAME_CHESSMASTER_CHESSBOARD_CHESS_PIECE_CHARIOT_H_ */
