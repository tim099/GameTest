#include "class/game/chessMaster/chessboard/renju/piece/Stone.h"
#include "class/display/draw/drawObject/AllDrawObjects.h"
namespace CM {

Stone::Stone() {
	draw_piece1=Display::AllDrawObjects::get_cur_object()->get("renju/black");
	draw_piece2=Display::AllDrawObjects::get_cur_object()->get("renju/white");
	weight=1;
}
Stone::~Stone() {

}
void Stone::next_step(CM::Board<short int> *chess_board,
		int x,int y,Tim::vector<CM::Step> &next_step,int player){
	if(bound_check(x,y)){//in chess board
		return;
	}
	CM::Step cur_step;
	cur_step.add_move(0,0,player,1);
	for(int i=0;i<9;i++){
		for(int j=0;j<9;j++){
			if(chess_board->get(i,j)==0){
				cur_step.moves[0].x=i;
				cur_step.moves[0].y=j;
				next_step.push_back(cur_step);
			}
		}
	}
}
} /* namespace CM */
