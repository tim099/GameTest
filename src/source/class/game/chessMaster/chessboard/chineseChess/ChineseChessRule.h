#ifndef SOURCE_CLASS_GAME_CHESSMASTER_CHESSBOARD_CHINESECHESS_CHINESECHESSRULE_H_
#define SOURCE_CLASS_GAME_CHESSMASTER_CHESSBOARD_CHINESECHESS_CHINESECHESSRULE_H_

#include "class/game/chessMaster/chessboard/Rule.h"

namespace CM {

class ChineseChessRule: public Rule {
public:
	ChineseChessRule();
	virtual ~ChineseChessRule();
	virtual int check_winner(CM::Board<short int> *chess_board);
};

} /* namespace CM */

#endif /* SOURCE_CLASS_GAME_CHESSMASTER_CHESSBOARD_CHINESECHESS_CHINESECHESSRULE_H_ */
