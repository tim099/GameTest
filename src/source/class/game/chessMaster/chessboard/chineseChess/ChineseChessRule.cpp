#include "class/game/chessMaster/chessboard/chineseChess/ChineseChessRule.h"

namespace CM {

ChineseChessRule::ChineseChessRule() {

}
ChineseChessRule::~ChineseChessRule() {

}
int ChineseChessRule::check_winner(CM::Board<short int> *chess_board){
	return chess_board->piece_num[0];

}
} /* namespace CM */
