#include "class/game/chessMaster/chessboard/chess/piece/Horse.h"
#include "class/display/draw/drawObject/AllDrawObjects.h"
#include "class/game/chessMaster/chessboard/ChessBoard.h"
namespace CM {

Horse::Horse() {
	draw_piece1=AllDrawObjects::get_cur_object()->get("chineseChess/red_horse");
	draw_piece2=AllDrawObjects::get_cur_object()->get("chineseChess/black_horse");
	weight=30;
}
Horse::~Horse() {

}
void Horse::next_step(Tim::Array2D<short int> *chess_board,
		glm::ivec2 cur_step,std::vector<int> &next_step,int player){
	int x=cur_step.x,y=cur_step.y;
	int i,j;
	i=x+1;
	j=y+2;
	if(bound_check(i,j)&&chess_board->get(x,y+1)==0&&chess_board->get(i,j)*player<=0){
		next_step.push_back(i);
		next_step.push_back(j);
	}
	i=x-1;
	j=y+2;
	if(bound_check(i,j)&&chess_board->get(x,y+1)==0&&chess_board->get(i,j)*player<=0){
		next_step.push_back(i);
		next_step.push_back(j);
	}
	i=x+1;
	j=y-2;
	if(bound_check(i,j)&&chess_board->get(x,y-1)==0&&chess_board->get(i,j)*player<=0){
		next_step.push_back(i);
		next_step.push_back(j);
	}
	i=x-1;
	j=y-2;
	if(bound_check(i,j)&&chess_board->get(x,y-1)==0&&chess_board->get(i,j)*player<=0){
		next_step.push_back(i);
		next_step.push_back(j);
	}
	i=x+2;
	j=y+1;
	if(bound_check(i,j)&&chess_board->get(x+1,y)==0&&chess_board->get(i,j)*player<=0){
		next_step.push_back(i);
		next_step.push_back(j);
	}
	i=x+2;
	j=y-1;
	if(bound_check(i,j)&&chess_board->get(x+1,y)==0&&chess_board->get(i,j)*player<=0){
		next_step.push_back(i);
		next_step.push_back(j);
	}
	i=x-2;
	j=y+1;
	if(bound_check(i,j)&&chess_board->get(x-1,y)==0&&chess_board->get(i,j)*player<=0){
		next_step.push_back(i);
		next_step.push_back(j);
	}
	i=x-2;
	j=y-1;
	if(bound_check(i,j)&&chess_board->get(x-1,y)==0&&chess_board->get(i,j)*player<=0){
		next_step.push_back(i);
		next_step.push_back(j);
	}
}
} /* namespace CM */
