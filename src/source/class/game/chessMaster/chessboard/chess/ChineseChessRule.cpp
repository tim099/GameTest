#include "class/game/chessMaster/chessboard/chess/ChineseChessRule.h"

namespace CM {

ChineseChessRule::ChineseChessRule() {

}
ChineseChessRule::~ChineseChessRule() {

}
int ChineseChessRule::check_winner(Tim::Array2D<short int> *chess_board){
	int winner=0,type;
	for(int i=3;i<=5;i++){
		for(int j=0;j<=2;j++){
			type=chess_board->get(i,j);
			if(type==1)winner++;
			else if(type==-1)winner--;
		}
		for(int j=7;j<=9;j++){
			type=chess_board->get(i,j);
			if(type==1)winner++;
			else if(type==-1)winner--;
		}
	}
	return winner;
}
} /* namespace CM */
