#ifndef SOURCE_CLASS_GAME_CHESSMASTER_CHESSBOARD_CHESSBOARDDO_H_
#define SOURCE_CLASS_GAME_CHESSMASTER_CHESSBOARD_CHESSBOARDDO_H_

#include "class/display/draw/drawObject/DrawObject.h"

namespace CM {

class ChessBoardDO: public DrawObject {
public:
	ChessBoardDO();
	virtual ~ChessBoardDO();
protected:
	Model *model;
};

} /* namespace CM */

#endif /* SOURCE_CLASS_GAME_CHESSMASTER_CHESSBOARD_CHESSBOARDDO_H_ */
