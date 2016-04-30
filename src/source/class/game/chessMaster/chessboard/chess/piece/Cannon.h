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
			,std::vector<CM::Step> &next_step){
		CM::Step cur_step;
		cur_step.moves.push_back(Math::vec4<int>(x,y,0,-1));
		cur_step.moves.push_back(Math::vec4<int>(0,0,chess_board->get(x,y),1));

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
							cur_step.moves[1].x=i;
							cur_step.moves[1].y=j;
							next_step.push_back(cur_step);
						}
						break;
					}
					i+=dx;
					j+=dy*player;
				}
				break;
			}
			cur_step.moves[1].x=i;
			cur_step.moves[1].y=j;
			next_step.push_back(cur_step);

			i+=dx;
			j+=dy*player;
		}
	}
	virtual void next_step(Tim::Array2D<short int> *chess_board,
			int x,int y,std::vector<CM::Step> &next_step,int player);
};

} /* namespace CM */

#endif /* SOURCE_CLASS_GAME_CHESSMASTER_CHESSBOARD_CHESS_PIECE_CANNON_H_ */
