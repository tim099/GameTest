#include "class/game/chessMaster/chessboard/chess/piece/General.h"
#include "class/display/draw/drawObject/AllDrawObjects.h"
#include "class/game/chessMaster/chessboard/ChessBoard.h"
namespace CM {

General::General() {
	draw_piece1=AllDrawObjects::get_cur_object()->get("chineseChess/red_general");
	draw_piece2=AllDrawObjects::get_cur_object()->get("chineseChess/black_general");
	weight=9999;
}
General::~General() {

}
void General::next_step(Tim::Array2D<short int> *chess_board,
		int x,int y,std::vector<int> &next_step,int player){
	int i,j;
	i=x+1;
	j=y;
	if(bound_check(i,j)&&in_nine(i,j)&&chess_board->get(i,j)*player<=0){
		next_step.push_back(i);
		next_step.push_back(j);
	}
	i=x-1;
	j=y;
	if(bound_check(i,j)&&in_nine(i,j)&&chess_board->get(i,j)*player<=0){
		next_step.push_back(i);
		next_step.push_back(j);
	}
	i=x;
	j=y+1;
	if(bound_check(i,j)&&in_nine(i,j)&&chess_board->get(i,j)*player<=0){
		next_step.push_back(i);
		next_step.push_back(j);
	}
	i=x;
	j=y-1;
	if(bound_check(i,j)&&in_nine(i,j)&&chess_board->get(i,j)*player<=0){
		next_step.push_back(i);
		next_step.push_back(j);
	}
	i=x;
	j=y+player;
	int type;
	while(bound_check(i,j)){

		type=chess_board->get(i,j);
		if (type!=0){
			if(type==-player){
				next_step.push_back(i);
				next_step.push_back(j);
			}
			break;
		}
		j+=player;
	}
}
} /* namespace CM */
