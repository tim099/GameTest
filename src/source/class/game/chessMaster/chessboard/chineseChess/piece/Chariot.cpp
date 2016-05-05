#include "class/game/chessMaster/chessboard/chineseChess/piece/Chariot.h"
#include "class/display/draw/drawObject/AllDrawObjects.h"
#include "class/game/chessMaster/chessboard/ChessBoard.h"
namespace CM {

Chariot::Chariot() {
	draw_piece1=Display::AllDrawObjects::get_cur_object()->get("chineseChess/red_chariot");
	draw_piece2=Display::AllDrawObjects::get_cur_object()->get("chineseChess/black_chariot");
	weight=50;
}
Chariot::~Chariot() {

}

void Chariot::next_step(CM::Board<short int> *chess_board,
		int x,int y,Tim::vector<CM::Step> &next_step,int player){
	move_straight(chess_board,x,y,1,0,player,next_step);
	move_straight(chess_board,x,y,-1,0,player,next_step);
	move_straight(chess_board,x,y,0,1,player,next_step);
	move_straight(chess_board,x,y,0,-1,player,next_step);
}

} /* namespace CM */
