#include "class/tim/thread/ThreadPool.h"
#include <iostream>
namespace Tim {

ThreadPool::ThreadPool(int thread_num,int priority) {
	Thread* thread;
	distributeTask=new DistributeTask(this);
	for(int i=0;i<thread_num;i++){
		//thread=new Tim::Thread(NORMAL_PRIORITY_CLASS,this);
		thread=new Tim::Thread(priority,distributeTask);
		threads.push_back(thread);
		ready_q.push(thread);
	}
}
ThreadPool::~ThreadPool() {
	delete distributeTask;

	while(!task_q.empty()){
		if(task_q.front()->AutoTerminate()){
			delete task_q.front();
		}
		task_q.pop();
	}
	//std::cout<<"delete ThreadPool()"<<std::endl;
}
void ThreadPool::Terminate(){
	bool end_flag=false;
	distributeTask->Terminate();
	Thread* thread;
	while(!ready_q.empty()){
		thread=ready_q.front();
		ready_q.pop();
		if(ready_thread_terminate(thread)){
			end_flag=true;
		}
	}
	if(end_flag)delete this;
}
bool ThreadPool::ready_thread_terminate(Thread* thread){
	Distribute_Mutex.wait_for_this();
	bool end_flag=false;
	for(unsigned i=0;i<threads.size();i++){
		if(threads.at(i)==thread){
			threads.at(i)=threads.back();
			threads.pop_back();
			break;
		}
	}
	thread->Terminate();

	if(threads.empty()){
		end_flag=true;
	}
	Distribute_Mutex.release();
	return end_flag;
}
void ThreadPool::push_task(Task* task){
	Distribute_Mutex.wait_for_this();
	if(!ready_q.empty()){
		ready_q.front()->push_task(task);
		ready_q.front()->start();
		ready_q.pop();
	}else{
		task_q.push(task);
	}
	Distribute_Mutex.release();
}

void ThreadPool::distribute_task(Tim::Thread* thread){
	Distribute_Mutex.wait_for_this();
	if(!task_q.empty()){
		thread->push_task(task_q.front());
		task_q.pop();
	}else{
		ready_q.push(thread);
	}
	Distribute_Mutex.release();
}
} /* namespace Tim */
