#include "class/game/chessMaster/AI/AI.h"
#include "class/game/chessMaster/chessboard/ChessBoard.h"
#include "class/game/chessMaster/AI/TaskComputeScore.h"
#include "class/game/chessMaster/AI/TaskAI.h"
#include <stdlib.h>
#include <time.h>
#include <algorithm>
#include <iostream>
#include <GL/glfw3.h>
#include <cmath>
#include <iomanip>
namespace CM {

AI::AI() {
	start_time=0;
	board=0;
	search_done=false;
	searching=false;
	traning_mode=false;
	total_compute=0;
	total_test=0;
	steps_pool=new Tim::ObjPool<Tim::ObjPool<Tim::vector<CM::Step> > >;
}
AI::~AI() {
	delete steps_pool;
}
void AI::search_start(Tim::ThreadPool *pool,
		CM::ChessBoard* chess_board,int player,int depth,int pruning){
	if(searching||search_done){
		return;
	}
	searching=true;
	CM::TaskAI* task=new CM::TaskAI(this,pool,chess_board,player,depth,pruning);
	pool->push_task(task);
	//task->join();
	//find_best_step(pool,chess_board,player,depth,pruning);
}
void AI::test(CM::Board<short int> *chess_board,
		int player,int depth,Tim::ObjPool<Tim::vector<CM::Step> >*steps_pool){
	if(depth==0){
		board->evaluate_score(chess_board, player);
		total_test++;
		return;
	}
	Tim::vector<CM::Step>* next_step=steps_pool->create();
	board->find_next_step(chess_board,player,*next_step);
	for (unsigned i = 0; i < next_step->size(); i++) {
		(*next_step)[i].move(chess_board);
		test(chess_board,-player, depth - 1,steps_pool);
		(*next_step)[i].undo(chess_board);
	}
	steps_pool->free(next_step);
}
CM::Step AI::find_best_step(Tim::ThreadPool* pool,CM::ChessBoard* _chess_board,int player,
		int depth,int pruning){
	total_compute=0;
	board=_chess_board;
	std::cout<<"AI::find_best_step start"<<std::endl;
	/*
	total_test=0;
	start_time=glfwGetTime();
	Tim::ObjPool<Tim::vector<CM::Step> >*tmp_pool=steps_pool->create();
	CM::Board<short int> *clone_board=new CM::Board<short int>(board->chess_board);
	test(clone_board,1,4,tmp_pool);
	delete clone_board;
	steps_pool->free(tmp_pool);

	std::cout<<"total test:"<<total_test<<std::endl;
	std::cout<<"test time used:"<<(float)(glfwGetTime()-start_time)<<std::endl;
	*/

	start_time=glfwGetTime();


	CM::Board<short int> *cb=new CM::Board<short int>(board->chess_board);
	CM::Step best=find_best_step(pool,cb,player,depth,pruning,true);
	delete cb;


	best_step=best;
	float time_used=(glfwGetTime()-start_time);
	std::cout<<"total time used:"<<time_used<<std::endl;
	std::cout<<"total_compute="<<total_compute<<",compute per second="
			<< std::fixed << std::setprecision(4)<<total_compute/time_used<<std::endl;
	std::cout<<"best score="<<best.score<<std::endl;
	search_done=true;
	searching=false;
	std::cout<<"AI::find_best_step end"<<std::endl;
	return best;
}
int AI::evaluate_score(CM::Board<short int> *chess_board,
		int player,int depth,int pruning,bool max,
		Tim::ObjPool<Tim::vector<CM::Step> >* steps_pool){
	CM::Step *cur;
	int best_score,cur_score;
	best_score=max?-MAX:MAX;

	Tim::vector<CM::Step>* next_step=steps_pool->create();
	board->find_next_step(chess_board,player,*next_step);

	bool end=false;
	unsigned step_size=next_step->size();
	CM::Rule *rule=board->rule;
	for (unsigned i = 0;(i<step_size)&&!end; i++) {
		cur = &((*next_step)[i]);
		cur->move(chess_board);
		if (!rule->check_winner(chess_board)) {//no player win yet
			if (depth <= 1) {//compute score
				total_compute++;
				cur_score = (max?-1:1)*board->evaluate_score(chess_board,-player);
			} else {//do backtracking
				cur_score = evaluate_score(chess_board, -player,
						depth - 1, best_score, !max,steps_pool);
			}
		} else {//one player win!!
			//std::cout<<"AI::evaluate_score winner find!!:"<<player<<std::endl;
			cur_score =(max?MAX:-MAX);
		}
		if ((max && cur_score > best_score) || (!max && cur_score < best_score)) {
			best_score = cur_score;
			if ((max && pruning < best_score) || (!max && pruning > best_score)) {
				//std::cout<<"pruning"<<std::endl;
				end=true;
			}
		}
		cur->undo(chess_board);
	}
	steps_pool->free(next_step);

	return best_score;
}
double AI::get_node_score(int wins,int simulations){
	return 10*(((double)wins-0.5*simulations+1.0)
			/((double)simulations+1.0));

}
void AI::get_node_scores(Tim::vector<CM::Step> &next_step,
		CM::Board<short int> *chess_board,std::vector<int>&node_scores,
		float &SD,float &avg_node_score){
	static const double visit_score=10.0;//the score of unexplored node
	CM::StepNode *cur_node=board->get_cur_node();
	CM::StepNode *next_node;
	float total_node_score;

	//int total_simulations=0;
	CM::Step *cur;

	total_node_score=0;
	float total_node=0;
	int node_score;
	for(unsigned i=0;i<next_step.size();i++){
		cur=&next_step[i];
		cur->move(chess_board);
		next_node=board->mct->find(cur_node,(*cur));
		if(next_node){
			//total_simulations+=next_node->data.simulations;
			node_score=get_node_score(next_node->data.wins,next_node->data.simulations);
			total_node++;
		}else{
			node_score=visit_score;
			total_node++;
		}
		//std::cout<<"node score="<<node_score<<std::endl;
		node_scores.push_back(node_score);
		total_node_score+=node_score;

		cur->undo(chess_board);
	}
	avg_node_score=total_node_score/total_node;
	SD=0;
	float delta;
	for(unsigned i=0;i<node_scores.size();i++){
		delta=node_scores.at(i)-avg_node_score;
		SD+=delta*delta;
	}
	SD=sqrt(SD/node_scores.size());
	std::cout<<"avg_node_score="<<avg_node_score<<std::endl;
	std::cout<<"SD="<<SD<<std::endl;

}
CM::Step AI::find_best_step(Tim::ThreadPool* pool,CM::Board<short int> *chess_board,
		int player,int depth,int pruning,bool max){
	//std::cout<<"AI::find_best_step depth="<<depth<<std::endl;

	CM::Step *cur;
	CM::Step best;
	int max_num=0;
	best.score=max?-MAX:MAX;
	Tim::vector<CM::Step> next_step;


	board->find_next_step(chess_board,player,next_step);
	std::vector<CM::TaskComputeScore*> tasks;
	CM::TaskComputeScore* task;
	std::vector<CM::Board<short int>*>prev_boards;

	CM::Board<short int>* tmp_board=new CM::Board<short int>(chess_board);
	for(int i=(board->steps.size()-1);(i>=0&&(board->steps.size()-i)<8);i--){
		CM::Step step=board->steps.at(i);
		step.undo(tmp_board);
		prev_boards.push_back(new CM::Board<short int>(tmp_board));
	}
	delete tmp_board;
	bool repeat;
	std::vector<Tim::ObjPool<Tim::vector<CM::Step> >* >tmp_pools;

	float SD;//standard deviation
	float avg_node_score;
	std::vector<int>node_scores;
	get_node_scores(next_step,chess_board,node_scores,SD,avg_node_score);

	CM::StepNode *next_node,*cur_node=board->get_cur_node();;
	for(unsigned i=0;i<next_step.size();i++){
		cur=&next_step[i];
		cur->move(chess_board);
		repeat=false;

		for(unsigned i=0;i<prev_boards.size();i++){
			if((*prev_boards.at(i))==(*chess_board)){//repeat
				repeat=true;
				break;
			}
		}
		next_node=board->mct->find(cur_node,(*cur));
		if(!repeat){//&&(node_score+visit_score>avg_node_score)
			int winner=board->check_winner(chess_board);
			if(winner==0){
				if(depth<=1){
					total_compute++;
					if(max)cur->score=board->evaluate_score(chess_board,player);
					else cur->score=board->evaluate_score(chess_board,-player);
				}else{
					Tim::ObjPool<Tim::vector<CM::Step> >*tmp_pool=steps_pool->create();
					tmp_pools.push_back(tmp_pool);
					task=new CM::TaskComputeScore(this,cur,next_node,chess_board
							,-player,depth-1,best.score,!max,tmp_pool);
					tasks.push_back(task);
					pool->push_task(task);
				}
			}else{
				if(max){
					cur->score=(MAX+1000);
				}else{
					cur->score=-(MAX+1000);
				}
				//best=*cur;
				//std::cout<<"AI::find_best_step winner!=0"<<std::endl;
			}
		}else{
			if(max){
				cur->score=-(MAX+1000);
			}else{
				cur->score=(MAX-1000);
			}
		}
		cur->undo(chess_board);
	}
	for(unsigned i=0;i<tasks.size();i++){
		tasks.at(i)->join();
		delete tasks.at(i);
	}
	for(unsigned i=0;i<tmp_pools.size();i++){
		steps_pool->free(tmp_pools.at(i));
	}
	bool find=false;
	for(unsigned i=0;i<next_step.size();i++){
		cur=&next_step[i];

		cur->score+=((node_scores.at(i)-avg_node_score)/(SD+1.0));
		if(!find||(max&&cur->score>=best.score)||(!max&&cur->score<=best.score)){

			if(cur->score==best.score){
				max_num++;
				srand(time(NULL));
				if(rand()%max_num==0){
					find=true;
					best=*cur;
				}
			}else{
				find=true;
				max_num=0;
				best=*cur;
			}
		}
	}
	for(unsigned i=0;i<prev_boards.size();i++){
		delete prev_boards.at(i);
	}
	return best;
}

} /* namespace CM */
