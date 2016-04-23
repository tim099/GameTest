#include "class/game/chessMaster/AI/TaskAI.h"
#include "class/game/chessMaster/AI/AI.h"
#include <iostream>
namespace CM {

TaskAI::TaskAI(CM::AI *_ai,Tim::ThreadPool *_pool,
		CM::ChessBoard* _chess_board,int _player,int _depth,int _pruning) {
	ai=_ai;
	pool=_pool;
	chess_board=_chess_board;
	player=_player;
	depth=_depth;
	pruning=_pruning;
	auto_terminate=true;
}
TaskAI::~TaskAI() {
	//std::cout<<"TaskAI::~TaskAI()"<<std::endl;
}
void TaskAI::ExecuteTask(){
	ai->find_best_step(pool,chess_board,player,depth,pruning);
}
} /* namespace CM */
