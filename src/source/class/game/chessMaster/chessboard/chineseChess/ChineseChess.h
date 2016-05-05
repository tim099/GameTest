#ifndef SOURCE_CLASS_GAME_CHESSMASTER_CHESSBOARD_CHINESECHESS_CHINESECHESS_H_
#define SOURCE_CLASS_GAME_CHESSMASTER_CHESSBOARD_CHINESECHESS_CHINESECHESS_H_

#include "class/game/chessMaster/chessboard/ChessBoard.h"

namespace CM {

class ChineseChess: public ChessBoard {
public:
	ChineseChess();
	virtual ~ChineseChess();
	void create_pieces();
};

} /* namespace CM */

#endif /* SOURCE_CLASS_GAME_CHESSMASTER_CHESSBOARD_CHINESECHESS_CHINESECHESS_H_ */
