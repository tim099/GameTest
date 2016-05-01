#include "class/game/chessMaster/AI/TaskComputeScore.h"
#include "class/game/chessMaster/AI/AI.h"
#include <iostream>
namespace CM {

TaskComputeScore::TaskComputeScore(CM::AI *_ai,Step *_step,CM::StepNode *_cur_node,
		CM::Board<short int> *_chess_board,
		int _player,int _depth,int _pruning,bool _max,
		Tim::ObjPool<Tim::vector<CM::Step> > *_steps_pool) {
	step=_step;
	cur_node=_cur_node;
	ai=_ai;

	chess_board=new CM::Board<short int>(_chess_board);
	//std::cout<<"chess board="<<(int)chess_board<<","<<(int)_chess_board<<std::endl;
	player=_player;
	depth=_depth;
	pruning=_pruning;
	max=_max;
	steps_pool=_steps_pool;
}
TaskComputeScore::~TaskComputeScore() {
	//std::cout<<"TaskComputeScore::~TaskComputeScore"<<std::endl;
}
void TaskComputeScore::ExecuteTask(){
	//std::vector<CM::Step> *pool=steps_pool->create();
	step->score=ai->evaluate_score(chess_board,player,depth,pruning,max,steps_pool);
	//steps_pool->free(pool);

	//std::cout<<"TaskComputeScore::ExecuteTask() score="<<step->score<<std::endl;
	delete chess_board;
}
} /* namespace CM */
