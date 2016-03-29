#ifndef SOURCE_CLASS_GAME_CHESSMASTER_CHESSBOARD_CHESSBOARD_H_
#define SOURCE_CLASS_GAME_CHESSMASTER_CHESSBOARD_CHESSBOARD_H_
#include "class/tim/array/Array3D.h"
namespace CM {

class ChessBoard {
public:
	ChessBoard(int sizex=8,int sizey=2,int sizez=8);
	virtual ~ChessBoard();
	void init();
	Tim::Array3D<unsigned char> *board;
protected:

};

} /* namespace CM */

#endif /* SOURCE_CLASS_GAME_CHESSMASTER_CHESSBOARD_CHESSBOARD_H_ */
