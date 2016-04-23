#ifndef SOURCE_CLASS_GAME_CHESSMASTER_PIECE_PIECE_H_
#define SOURCE_CLASS_GAME_CHESSMASTER_PIECE_PIECE_H_
#include "class/tim/thread/mutex/Mutex.h"
#include "class/game/chessMaster/piece/Step.h"
#include <string>
#include <vector>
#include <glm/vec2.hpp>
#include "class/tim/lua/Lua.h"
#include <string>
class Position;
class DrawObject;
namespace CM {
class ChessBoard;

class Piece {
public:
	friend ChessBoard;
	Piece();
	virtual ~Piece();


	virtual void next_step(Tim::Array2D<short int> *chess_board,
			int x,int y,std::vector<CM::Step> &next_step,int player);
	void load_script(std::string path);
	void draw(Position* pos,int player);
	//unsigned char type;
	int weight;
protected:
	virtual void next_step(Tim::Array2D<short int> *chess_board,
			int x,int y,std::vector<int> &next_step,int player);
	Tim::Mutex* rule_mutex;
	DrawObject *draw_piece1;//player1's piece EX:black king
	DrawObject *draw_piece2;//player2's piece EX:white king
	std::string rule_path;
	Tim::Lua *rule;
};

} /* namespace CM */

#endif /* SOURCE_CLASS_GAME_CHESSMASTER_PIECE_PIECE_H_ */
