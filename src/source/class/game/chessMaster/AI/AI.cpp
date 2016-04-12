#include "class/game/chessMaster/AI/AI.h"
#include "class/game/chessMaster/chessboard/ChessBoard.h"
#include "class/game/chessMaster/AI/TaskComputeScore.h"

#include <stdlib.h>
#include <time.h>
#include <algorithm>
#include <iostream>
#include <GL/glfw3.h>
namespace CM {

AI::AI() {
	start_time=0;
	board=0;
	search_done=false;
	searching=false;
	total_compute=0;
}
AI::~AI() {

}
CM::Step AI::find_best_step(Tim::ThreadPool* pool,CM::ChessBoard* _chess_board,int player,int depth,int pruning){
	start_time=glfwGetTime();
	search_done=false;
	searching=true;
	total_compute=0;
	board=_chess_board;

	Tim::Array2D<short int> *cb=new Tim::Array2D<short int>(board->chess_board);
	CM::Step best=find_best_step(pool,cb,player,depth,pruning,true);
	delete cb;

	search_done=true;
	searching=false;
	best_step=best;
	std::cout<<"total time used:"<<(float)(glfwGetTime()-start_time)<<std::endl;
	std::cout<<"best score="<<best.score<<std::endl;
	return best;
}
int AI::get_score(Tim::Array2D<short int> *chess_board,
		int player,int depth,int pruning,bool max){
	//std::cout<<"AI::get_score depth="<<depth<<std::endl;



	CM::Step *cur;
	int best;
	best=max?-MAX:MAX;;
	std::vector<CM::Step> next_step;

	board->find_next_step(chess_board,player,next_step);
	//std::cout<<"step num="<<next_step.size()<<std::endl;
	for(unsigned i=0;i<next_step.size();i++){
		cur=&next_step.at(i);
		cur->move(chess_board);
		int winner=board->check_winner(chess_board);
		if(winner==0){
			if(depth<=1){
				total_compute++;
				if(max)cur->score=board->evaluate_score(chess_board,player);
				else cur->score=board->evaluate_score(chess_board,-player);
			}else{
				cur->score=get_score(chess_board,-player,depth-1,best,!max);
			}
		}else{
			if(max){
				cur->score=MAX;
			}else{
				cur->score=-MAX;
			}
		}
		if((max&&cur->score>best)||(!max&&cur->score<best)){
			best=cur->score;
			if((max&&(pruning)<best)||(!max&&(pruning)>best)){
				cur->undo(chess_board);
				return best;
			}
		}
		cur->undo(chess_board);
	}

	return best;
}
CM::Step AI::find_best_step(Tim::ThreadPool* pool,Tim::Array2D<short int> *chess_board,
		int player,int depth,int pruning,bool max){
	//std::cout<<"AI::find_best_step depth="<<depth<<std::endl;
	CM::Step *cur;
	CM::Step best;
	int max_num=0;
	best.score=max?-MAX:MAX;
	std::vector<CM::Step> next_step;

	board->find_next_step(chess_board,player,next_step);
	std::vector<CM::TaskComputeScore*> tasks;
	CM::TaskComputeScore* task;
	for(unsigned i=0;i<next_step.size();i++){
		cur=&next_step.at(i);
		cur->move(chess_board);
		int winner=board->check_winner(chess_board);
		if(winner==0){
			if(depth<=1){
				total_compute++;
				if(max)cur->score=board->evaluate_score(chess_board,player);
				else cur->score=board->evaluate_score(chess_board,-player);
			}else{
				task=new CM::TaskComputeScore(this,cur,chess_board
						,-player,depth-1,best.score,!max);
				tasks.push_back(task);
				pool->push_task(task);
			}
		}else{
			if(max){
				cur->score=(MAX+1);
			}else{
				cur->score=-(MAX-1);
			}
			best=*cur;
		}
		cur->undo(chess_board);
	}
	for(unsigned i=0;i<tasks.size();i++){
		tasks.at(i)->join();
		while(!tasks.at(i)->Done()){
			//std::cout<<"wait"<<std::endl;
		}
		delete tasks.at(i);
	}
	for(unsigned i=0;i<next_step.size();i++){
		cur=&next_step.at(i);
		if((max&&cur->score>=best.score)||(!max&&cur->score<=best.score)){
			if(cur->score==best.score){
				max_num++;
				srand(time(NULL));
				if(rand()%max_num==0){
					best=*cur;
				}
			}else{
				max_num=0;
				best=*cur;
			}
		}
	}
	return best;
}

} /* namespace CM */
