#ifndef SOURCE_CLASS_GAME_CHESSMASTER_CHESSBOARD_RENJU_RENJURULE_H_
#define SOURCE_CLASS_GAME_CHESSMASTER_CHESSBOARD_RENJU_RENJURULE_H_
#include "class/game/chessMaster/chessboard/Rule.h"
namespace CM {

class RenjuRule : public Rule {
public:
	RenjuRule();
	virtual ~RenjuRule();
	virtual int check_winner(CM::Board<short int> *chess_board);
};

} /* namespace CM */

#endif /* SOURCE_CLASS_GAME_CHESSMASTER_CHESSBOARD_RENJU_RENJURULE_H_ */
