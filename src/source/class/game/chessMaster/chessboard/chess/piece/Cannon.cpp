#include "class/game/chessMaster/chessboard/chess/piece/Cannon.h"
#include "class/display/draw/drawObject/AllDrawObjects.h"
#include "class/game/chessMaster/chessboard/ChessBoard.h"
namespace CM {

Cannon::Cannon() {
	draw_piece1=AllDrawObjects::get_cur_object()->get("chineseChess/red_cannon");
	draw_piece2=AllDrawObjects::get_cur_object()->get("chineseChess/black_cannon");
	weight=50;
}
Cannon::~Cannon() {

}
void Cannon::cannon_move(Tim::Array2D<short int> *chess_board,
		int x,int y,int dx,int dy,int player
		,std::vector<int> &next_step){
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
						next_step.push_back(i);
						next_step.push_back(j);
					}
					break;
				}
				i+=dx;
				j+=dy*player;
			}
			break;
		}
		next_step.push_back(i);
		next_step.push_back(j);

		i+=dx;
		j+=dy*player;
	}
}
void Cannon::next_step(Tim::Array2D<short int> *chess_board,
		glm::ivec2 cur_step,std::vector<int> &next_step,int player){
	cannon_move(chess_board,cur_step.x,cur_step.y,1,0,player,next_step);
	cannon_move(chess_board,cur_step.x,cur_step.y,-1,0,player,next_step);
	cannon_move(chess_board,cur_step.x,cur_step.y,0,1,player,next_step);
	cannon_move(chess_board,cur_step.x,cur_step.y,0,-1,player,next_step);
}
} /* namespace CM */
