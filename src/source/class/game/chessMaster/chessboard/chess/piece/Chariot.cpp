#include "class/game/chessMaster/chessboard/chess/piece/Chariot.h"
#include "class/display/draw/drawObject/AllDrawObjects.h"
#include "class/game/chessMaster/chessboard/ChessBoard.h"
namespace CM {

Chariot::Chariot() {
	draw_piece1=AllDrawObjects::get_cur_object()->get("chineseChess/red_chariot");
	draw_piece2=AllDrawObjects::get_cur_object()->get("chineseChess/black_chariot");
	weight=50;
}
Chariot::~Chariot() {

}
void Chariot::move_straight(Tim::Array2D<short int> *chess_board,
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
void Chariot::next_step(Tim::Array2D<short int> *chess_board,
		glm::ivec2 cur_step,std::vector<int> &next_step,int player){
	move_straight(chess_board,cur_step.x,cur_step.y,1,0,player,next_step);
	move_straight(chess_board,cur_step.x,cur_step.y,-1,0,player,next_step);
	move_straight(chess_board,cur_step.x,cur_step.y,0,1,player,next_step);
	move_straight(chess_board,cur_step.x,cur_step.y,0,-1,player,next_step);
}
} /* namespace CM */
