#ifndef SOURCE_CLASS_GAME_CHESSMASTER_AI_TASKCOMPUTESCORE_H_
#define SOURCE_CLASS_GAME_CHESSMASTER_AI_TASKCOMPUTESCORE_H_
#include "class/tim/thread/task/Task.h"
#include "class/game/chessMaster/chessboard/Board.h"
#include "class/tim/objectpool/ObjPool.h"
#include "class/tim/array/vector.h"
namespace CM {
class AI;
class ChessBoard;
class Step;
class StepNode;
class TaskComputeScore: public Tim::Task {
public:
	TaskComputeScore(CM::AI *ai,Step *step,CM::StepNode *cur_node,
			CM::Board<short int> *chess_board,
			int player,int depth,int pruning,bool max,
			Tim::ObjPool<Tim::vector<CM::Step> > *steps_pool);
	virtual ~TaskComputeScore();
	Step *step;
	Tim::ObjPool<Tim::vector<CM::Step> > *steps_pool;
protected:
	virtual void ExecuteTask();
	CM::AI *ai;
	CM::StepNode *cur_node;
	CM::Board<short int> *chess_board;

	int player;
	int depth;
	int pruning;
	bool max;
};

} /* namespace CM */

#endif /* SOURCE_CLASS_GAME_CHESSMASTER_AI_TASKCOMPUTESCORE_H_ */
