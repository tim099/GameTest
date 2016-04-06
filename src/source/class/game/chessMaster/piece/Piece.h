#ifndef SOURCE_CLASS_GAME_CHESSMASTER_PIECE_PIECE_H_
#define SOURCE_CLASS_GAME_CHESSMASTER_PIECE_PIECE_H_
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

	void next_step(glm::ivec2 cur_step,std::vector<glm::ivec2> &next_step,bool player1);
	void load_script(std::string path);
	void draw(Position* pos,bool player1);
	unsigned char type;
	int weight;
protected:
	static int bound_check(lua_State *L);
	static int get_board(lua_State *L);
	DrawObject *draw_piece1;//player1's piece EX:black king
	DrawObject *draw_piece2;//player2's piece EX:white king
	std::string rule_path;
	Tim::Lua *rule;
};

} /* namespace CM */

#endif /* SOURCE_CLASS_GAME_CHESSMASTER_PIECE_PIECE_H_ */
