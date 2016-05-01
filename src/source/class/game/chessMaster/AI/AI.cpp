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
namespace CM {

AI::AI() {
	start_time=0;
	board=0;
	search_done=false;
	searching=false;
	total_compute=0;
	total_test=0;
	steps_pool=new Tim::ObjPool<Tim::ObjPool<Tim::vector<CM::Step> > >;
}
AI::~AI() {
	delete steps_pool;
}
void AI::search_start(Tim::ThreadPool *pool,
		CM::ChessBoard* chess_board,int player,int depth,int pruning){
	search_done=false;
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
		 // next_step[i].moves.push_back(Math::vec4<int> (0,0,0,0));
		 //board->check_winner(board->chess_board);
		 //board->evaluate_score(board->chess_board,1);
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

	/*
	total_test=0;
	start_time=glfwGetTime();
	Tim::ObjPool<Tim::vector<CM::Step> >*tmp_pool=steps_pool->create();
	Tim::Array2D<short int> *clone_board=new Tim::Array2D<short int>(board->chess_board);
	test(clone_board,1,4,tmp_pool);
	delete clone_board;
	steps_pool->free(tmp_pool);

	std::cout<<"total test:"<<total_test<<std::endl;
	std::cout<<"test time used:"<<(float)(glfwGetTime()-start_time)<<std::endl;
	*/

	start_time=glfwGetTime();
	search_done=false;
	searching=true;


	CM::Board<short int> *cb=new CM::Board<short int>(board->chess_board);
	CM::Step best=find_best_step(pool,cb,player,depth,pruning,true);
	delete cb;

	search_done=true;
	searching=false;
	best_step=best;
	std::cout<<"total time used:"<<(float)(glfwGetTime()-start_time)<<std::endl;
	std::cout<<"best score="<<best.score<<std::endl;
	return best;
}
int AI::evaluate_score(CM::Board<short int> *chess_board,
		int player,int depth,int pruning,bool max,
		Tim::ObjPool<Tim::vector<CM::Step> >*steps_pool){
	CM::Step *cur;
	int best,cur_score;
	best=max?-MAX:MAX;

	Tim::vector<CM::Step>* next_step=steps_pool->create();
	next_step->clear();

	board->find_next_step(chess_board,player,*next_step);
	bool end=false;
	unsigned step_size=next_step->size();

	for (unsigned i = 0;(i<step_size)&&!end; i++) {
		cur = &(*next_step)[i];
		cur->move(chess_board);
		if (board->check_winner(chess_board) == 0) {//no player win yet
			if (depth <= 1) {//compute score
				total_compute++;
				if (max){
					cur_score = board->evaluate_score(chess_board, player);
				}else{
					cur_score = board->evaluate_score(chess_board, -player);
				}
			} else {//do backtracking
				cur_score = evaluate_score(chess_board, -player,
						depth - 1, best, !max,steps_pool);
			}
		} else {//one player win!!
			if (max) {
				cur_score = MAX;
			} else {
				cur_score = -MAX;
			}
		}
		if ((max && cur_score > best) || (!max && cur_score < best)) {
			best = cur_score;
			if ((max && pruning < best) || (!max && pruning > best)) {
				end=true;
			}
		}
		cur->undo(chess_board);
	}
	steps_pool->free(next_step);

	return best;
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

	CM::StepNode *cur_node=board->get_cur_node();
	CM::StepNode *next_node;
	float node_score;
	bool repeat,score_exist;
	std::vector<Tim::ObjPool<Tim::vector<CM::Step> >* >tmp_pools;
	for(unsigned i=0;i<next_step.size();i++){
		cur=&next_step[i];
		cur->move(chess_board);
		repeat=false;
		score_exist=false;

		for(unsigned i=0;i<prev_boards.size();i++){
			if((*prev_boards.at(i))==(*chess_board)){//repeat
				repeat=true;
				//std::cout<<"repeat"<<std::endl;
				break;
			}
		}
		if(depth>5){
			next_node=board->mct->find_and_expand(cur_node,(*cur));
		}else{
			next_node=board->mct->find(cur_node,(*cur));
		}

		if(next_node){
			if(next_node->data.depth>=depth){
				score_exist=true;
				cur->score=next_node->data.score;
				//std::cout<<"depth:"<<depth<<"score exist="<<next_node->data.score<<std::endl;
			}else{
				//std::cout<<"score not exist"<<std::endl;
			}
		}
		if(!repeat&&!score_exist){
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
					cur->score=-(MAX-1000);
				}
				//best=*cur;
				//std::cout<<"AI::find_best_step winner!=0"<<std::endl;
			}
		}else{
			if(score_exist){

			}else if(repeat){
				if(max){
					cur->score=-(MAX+1000);
				}else{
					cur->score=(MAX-1000);
				}
				//std::cout<<"repeat"<<std::endl;
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
	static const double visit_score=1.0;
	for(unsigned i=0;i<next_step.size();i++){
		cur=&next_step[i];
		if((next_node=board->mct->find(cur_node,(*cur)))){
			if(next_node->data.simulations>0){
				//std::cout<<"wins="<<next_node->data.wins<<std::endl;
				//std::cout<<"simulations="<<next_node->data.simulations<<std::endl;
				node_score=10*((double)(next_node->data.wins-0.5*next_node->data.simulations+1.0)
						/sqrt((double)next_node->data.simulations+1.0));
			}else{
				node_score=visit_score;
			}
			if(next_node->data.depth<depth){
				next_node->data.depth=depth;
				next_node->data.score=cur->score;
			}
		}else{
			node_score=visit_score;
			//node_score=200.0;//try new move!!
		}
		//std::cout<<"cur->score="<<cur->score<<std::endl;
		if(node_score!=visit_score){
			std::cout<<"node_score="<<node_score<<std::endl;
		}
		cur->score+=node_score;
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
	for(unsigned i=0;i<prev_boards.size();i++){
		delete prev_boards.at(i);
	}
	return best;
}

} /* namespace CM */
