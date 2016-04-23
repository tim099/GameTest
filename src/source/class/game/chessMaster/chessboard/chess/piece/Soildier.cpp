#include "class/game/chessMaster/chessboard/chess/piece/Soildier.h"
#include "class/display/draw/drawObject/AllDrawObjects.h"
#include "class/game/chessMaster/chessboard/ChessBoard.h"
namespace CM {

Soildier::Soildier() {
	draw_piece1=AllDrawObjects::get_cur_object()->get("chineseChess/red_soldier");
	draw_piece2=AllDrawObjects::get_cur_object()->get("chineseChess/black_soldier");
	weight=7;
}
Soildier::~Soildier() {

}
void Soildier::next_step(Tim::Array2D<short int> *chess_board,
		int x,int y,std::vector<int> &next_step,int player){
	int i,j;
	i=x;
	j=y+1*player;
	if(bound_check(i,j)&&chess_board->get(i,j)*player<=0){
		next_step.push_back(i);
		next_step.push_back(j);
	}

	if((player==1&&y>=5)||(player==-1&&y<5)){
		i=x+1;
		j=y;
		if(bound_check(i,j)&&chess_board->get(i,j)*player<=0){
			next_step.push_back(i);
			next_step.push_back(j);
		}
		i=x-1;
		j=y;
		if(bound_check(i,j)&&chess_board->get(i,j)*player<=0){
			next_step.push_back(i);
			next_step.push_back(j);
		}
	}
}
} /* namespace CM */
