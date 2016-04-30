#ifndef SOURCE_CLASS_GAME_CHESSMASTER_AI_TASKAI_H_
#define SOURCE_CLASS_GAME_CHESSMASTER_AI_TASKAI_H_

#include "class/tim/thread/task/Task.h"
#include "class/tim/thread/ThreadPool.h"
namespace CM {
class AI;
class ChessBoard;
class TaskAI: public Tim::Task {
public:
	TaskAI(CM::AI *ai,Tim::ThreadPool *pool,
			CM::ChessBoard* chess_board,int player,
			int depth,int pruning);
	virtual ~TaskAI();
protected:
	virtual void ExecuteTask();
	CM::AI *ai;
	Tim::ThreadPool *pool;
	CM::ChessBoard* chess_board;
	int player;
	int depth;
	int pruning;

};

} /* namespace CM */

#endif /* SOURCE_CLASS_GAME_CHESSMASTER_AI_TASKAI_H_ */
