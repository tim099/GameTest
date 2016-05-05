#ifndef SOURCE_CLASS_GAME_CHESSMASTER_CHESSBOARD_CHINESECHESS_PIECE_CHARIOT_H_
#define SOURCE_CLASS_GAME_CHESSMASTER_CHESSBOARD_CHINESECHESS_PIECE_CHARIOT_H_
#include "class/game/chessMaster/piece/Piece.h"
namespace CM {

class Chariot : public Piece{
public:
	Chariot();
	virtual ~Chariot();
	inline bool bound_check(const int& x,const int &y){
		if(x>=0&&y>=0&&x<=8&&y<=9){
			return true;
		}
		return false;
	}
	inline void move_straight(CM::Board<short int> *chess_board,
			int x,int y,int dx,int dy,int player
			,Tim::vector<CM::Step> &next_step){
		CM::Step cur_step;
		cur_step.add_move(x,y,0,-1);
		cur_step.add_move(0,0,chess_board->get(x,y),1);
		int i=x+dx;
		int j=y+dy*player;
		int type;
		while(bound_check(i,j)){
			type=chess_board->get(i,j);
			if (type*player>0)break;//stop by player's own piece
			cur_step.moves[1].x=i;
			cur_step.moves[1].y=j;
			next_step.push_back(cur_step);
			if (type*player<0)break;//attack enemy and stop here
			i+=dx;
			j+=dy*player;
		}
	}
	virtual void next_step(CM::Board<short int> *chess_board,
			int x,int y,Tim::vector<CM::Step> &next_step,int player);

};

} /* namespace CM */

#endif /* SOURCE_CLASS_GAME_CHESSMASTER_CHESSBOARD_CHINESECHESS_PIECE_CHARIOT_H_ */
