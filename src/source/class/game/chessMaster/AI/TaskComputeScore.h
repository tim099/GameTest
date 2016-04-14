#ifndef SOURCE_CLASS_GAME_CHESSMASTER_AI_TASKCOMPUTESCORE_H_
#define SOURCE_CLASS_GAME_CHESSMASTER_AI_TASKCOMPUTESCORE_H_
#include "class/tim/thread/task/Task.h"
#include "class/tim/array/Array2D.h"
namespace CM {
class AI;
class ChessBoard;
class Step;
class StepNode;
class TaskComputeScore: public Tim::Task {
public:
	TaskComputeScore(CM::AI *ai,Step *step,CM::StepNode *cur_node,
			Tim::Array2D<short int> *chess_board,
			int player,int depth,int pruning,bool max);
	virtual ~TaskComputeScore();
	Step *step;
protected:
	virtual void ExecuteTask();
	CM::AI *ai;
	CM::StepNode *cur_node;
	Tim::Array2D<short int> *chess_board;
	int player;
	int depth;
	int pruning;
	bool max;
};

} /* namespace CM */

#endif /* SOURCE_CLASS_GAME_CHESSMASTER_AI_TASKCOMPUTESCORE_H_ */
