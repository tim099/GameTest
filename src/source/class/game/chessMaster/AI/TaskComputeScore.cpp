#include "class/game/chessMaster/AI/TaskComputeScore.h"
#include "class/game/chessMaster/AI/AI.h"
#include <iostream>
namespace CM {

TaskComputeScore::TaskComputeScore(CM::AI *_ai,Step *_step,Tim::Array2D<short int> *_chess_board,
		int _player,int _depth,int _pruning,bool _max) {
	step=_step;
	ai=_ai;
	chess_board=new Tim::Array2D<short int>(_chess_board);
	//std::cout<<"chess board="<<(int)chess_board<<","<<(int)_chess_board<<std::endl;
	player=_player;
	depth=_depth;
	pruning=_pruning;
	max=_max;
}
TaskComputeScore::~TaskComputeScore() {

}
void TaskComputeScore::ExecuteTask(){

	step->score=ai->get_score(chess_board,player,depth,pruning,max);
	//std::cout<<"TaskComputeScore::ExecuteTask() score="<<step->score<<std::endl;
	delete chess_board;
}
} /* namespace CM */
