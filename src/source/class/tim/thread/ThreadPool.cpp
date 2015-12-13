#include "class/tim/thread/ThreadPool.h"
#include <iostream>
namespace Tim {

ThreadPool::ThreadPool(int thread_num) {
	Thread* thread;
	distributeTask=new DistributeTask(this);
	Distribute_Mutex=new Tim::Mutex();
	for(int i=0;i<thread_num;i++){
		//thread=new Tim::Thread(NORMAL_PRIORITY_CLASS,this);
		thread=new Tim::Thread(NORMAL_PRIORITY_CLASS,distributeTask);
		threads.push_back(thread);
		ready_q.push(thread);
	}
}
ThreadPool::~ThreadPool() {
	delete distributeTask;
	delete Distribute_Mutex;
	while(!threads.empty()){
		threads.back()->Terminate();
		threads.pop_back();
	}
}
void ThreadPool::push_task(Task* task){
	Distribute_Mutex->wait_for_this();
	if(!ready_q.empty()){
		ready_q.front()->push_task(task);
		ready_q.front()->start();
		ready_q.pop();
	}else{
		task_q.push(task);
	}
	Distribute_Mutex->release();
}

void ThreadPool::distribute_task(Tim::Thread* thread){
	Distribute_Mutex->wait_for_this();
	if(!task_q.empty()){
		thread->push_task(task_q.front());
		//thread->start();
		task_q.pop();
	}else{
		ready_q.push(thread);
	}
	Distribute_Mutex->release();
}
} /* namespace Tim */
