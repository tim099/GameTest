#include "class/game/chessMaster/chessboard/chess/piece/Advisor.h"
#include "class/display/draw/drawObject/AllDrawObjects.h"
#include "class/game/chessMaster/chessboard/ChessBoard.h"
namespace CM {

Advisor::Advisor() {
	draw_piece1=Display::AllDrawObjects::get_cur_object()->get("chineseChess/red_advisor");
	draw_piece2=Display::AllDrawObjects::get_cur_object()->get("chineseChess/black_advisor");
	weight=10;
}
Advisor::~Advisor() {

}
void Advisor::next_step(Tim::Array2D<short int> *chess_board,
		int x,int y,Tim::vector<CM::Step> &next_step,int player){
	CM::Step cur_step;
	cur_step.add_move(x,y,0,-1);
	cur_step.add_move(0,0,chess_board->get(x,y),1);

	int i,j;
	i=x+1;
	j=y+1;
	if(bound_check(i,j)&&in_nine(i,j)&&chess_board->get(i,j)*player<=0){
		cur_step.moves[1].x=i;
		cur_step.moves[1].y=j;
		next_step.push_back(cur_step);
	}
	i=x-1;
	j=y+1;
	if(bound_check(i,j)&&in_nine(i,j)&&chess_board->get(i,j)*player<=0){
		cur_step.moves[1].x=i;
		cur_step.moves[1].y=j;
		next_step.push_back(cur_step);
	}
	i=x+1;
	j=y-1;
	if(bound_check(i,j)&&in_nine(i,j)&&chess_board->get(i,j)*player<=0){
		cur_step.moves[1].x=i;
		cur_step.moves[1].y=j;
		next_step.push_back(cur_step);
	}
	i=x-1;
	j=y-1;
	if(bound_check(i,j)&&in_nine(i,j)&&chess_board->get(i,j)*player<=0){
		cur_step.moves[1].x=i;
		cur_step.moves[1].y=j;
		next_step.push_back(cur_step);
	}
}
} /* namespace CM */
