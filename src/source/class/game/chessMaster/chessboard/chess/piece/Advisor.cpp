#include "class/game/chessMaster/chessboard/chess/piece/Advisor.h"
#include "class/display/draw/drawObject/AllDrawObjects.h"
#include "class/game/chessMaster/chessboard/ChessBoard.h"
namespace CM {

Advisor::Advisor() {
	draw_piece1=AllDrawObjects::get_cur_object()->get("chineseChess/red_advisor");
	draw_piece2=AllDrawObjects::get_cur_object()->get("chineseChess/black_advisor");
	weight=10;
}
Advisor::~Advisor() {

}
void Advisor::next_step(Tim::Array2D<short int> *chess_board,
		glm::ivec2 cur_step,std::vector<int> &next_step,int player){
	int x=cur_step.x,y=cur_step.y;
	int i,j;
	i=x+1;
	j=y+1;
	if(bound_check(i,j)&&in_nine(i,j)&&chess_board->get(i,j)*player<=0){
		next_step.push_back(i);
		next_step.push_back(j);
	}
	i=x-1;
	j=y+1;
	if(bound_check(i,j)&&in_nine(i,j)&&chess_board->get(i,j)*player<=0){
		next_step.push_back(i);
		next_step.push_back(j);
	}
	i=x+1;
	j=y-1;
	if(bound_check(i,j)&&in_nine(i,j)&&chess_board->get(i,j)*player<=0){
		next_step.push_back(i);
		next_step.push_back(j);
	}
	i=x-1;
	j=y-1;
	if(bound_check(i,j)&&in_nine(i,j)&&chess_board->get(i,j)*player<=0){
		next_step.push_back(i);
		next_step.push_back(j);
	}
}
} /* namespace CM */
