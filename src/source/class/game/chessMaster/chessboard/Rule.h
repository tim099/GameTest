#ifndef SOURCE_CLASS_GAME_CHESSMASTER_CHESSBOARD_RULE_H_
#define SOURCE_CLASS_GAME_CHESSMASTER_CHESSBOARD_RULE_H_
#include "class/tim/lua/Lua.h"
#include "class/tim/array/Array2D.h"
#include "class/tim/thread/mutex/Mutex.h"
#include <string>
namespace CM {

class Rule {
public:
	Rule();
	virtual ~Rule();
	void load_rule(std::string path);
	virtual int check_winner(Tim::Array2D<short int> *chess_board);
	Tim::Lua *rule;
	Tim::Mutex* rule_mutex;
};

} /* namespace CM */

#endif /* SOURCE_CLASS_GAME_CHESSMASTER_CHESSBOARD_RULE_H_ */
