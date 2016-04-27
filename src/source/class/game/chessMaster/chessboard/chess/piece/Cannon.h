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
	inline void cannon_move(Tim::Array2D<short int> *chess_board,
			int x,int y,int dx,int dy,int player
			,std::vector<int> &next_step){
		int i=x+dx;
		int j=y+dy*player;
		int type;
		while(bound_check(i,j)){
			type=chess_board->get(i,j);
			if(type!=0){
				i+=dx;
				j+=dy*player;
				while(bound_check(i,j)){
					type=chess_board->get(i,j);
					if(type!=0){
						if(type*player<0){
							next_step.push_back(i);
							next_step.push_back(j);
						}
						break;
					}
					i+=dx;
					j+=dy*player;
				}
				break;
			}
			next_step.push_back(i);
			next_step.push_back(j);

			i+=dx;
			j+=dy*player;
		}
	}
	virtual void next_step(Tim::Array2D<short int> *chess_board,
			int x,int y,std::vector<int> &next_step,int player);
};

} /* namespace CM */

#endif /* SOURCE_CLASS_GAME_CHESSMASTER_CHESSBOARD_CHESS_PIECE_CANNON_H_ */
