#ifndef SOURCE_CLASS_GAME_CHESSMASTER_AI_AI_H_
#define SOURCE_CLASS_GAME_CHESSMASTER_AI_AI_H_
#include "class/game/chessMaster/piece/Step.h"
#include "class/tim/array/Array2D.h"
#include "class/tim/thread/ThreadPool.h"
#include "class/tim/objectpool/ObjPool.h"
#include "class/tim/array/vector.h"
#include "class/game/chessMaster/chessboard/Board.h"
namespace CM {
class ChessBoard;
class StepNode;
class TaskAI;
class TaskComputeScore;
class AI {
	static const int MAX=999999;
	friend TaskAI;
	friend TaskComputeScore;
public:
	AI();
	virtual ~AI();

	void search_start(Tim::ThreadPool *pool,
			CM::ChessBoard* chess_board,int player,int depth,int pruning);


	bool search_done;
	bool searching;
	CM::Step best_step;
	unsigned total_compute;
	float start_time;
protected:
	CM::Step find_best_step(Tim::ThreadPool* pool,CM::ChessBoard* chess_board,
			int player,int depth,int pruning);
	int evaluate_score(CM::Board<short int>* chess_board,
			int player,int depth,int pruning,bool max
			,Tim::ObjPool<Tim::vector<CM::Step> >*steps_pool);
	struct cmpmax{
	    inline bool operator() (const CM::Step& s1, const CM::Step& s2){
	        return (s1.score < s2.score);
	    }
	};
	struct cmpmin{
	    inline bool operator() (const CM::Step& s1, const CM::Step& s2){
	        return (s1.score > s2.score);
	    }
	};
	CM::Step find_best_step(Tim::ThreadPool* pool,CM::Board<short int> *chess_board,
			int player,int depth,int pruning,bool max);

	Tim::ObjPool<Tim::ObjPool<Tim::vector<CM::Step> > >*steps_pool;
	CM::ChessBoard* board;
	void test(CM::Board<short int> *chess_board,int player,int depth,Tim::ObjPool<Tim::vector<CM::Step> >*steps_pool);
	int total_test;
};

} /* namespace CM */

#endif /* SOURCE_CLASS_GAME_CHESSMASTER_AI_AI_H_ */
