#include "class/tim/thread/ThreadPool.h"
#include <iostream>
namespace Tim {

ThreadPool::ThreadPool(int thread_num,int priority) {
	Thread* thread;
	distributeTask=new DistributeTask(this);
	Distribute_Mutex=new Tim::Mutex();
	for(int i=0;i<thread_num;i++){
		//thread=new Tim::Thread(NORMAL_PRIORITY_CLASS,this);
		thread=new Tim::Thread(priority,distributeTask);
		threads.push_back(thread);
		ready_q.push(thread);
	}
}
ThreadPool::~ThreadPool() {

	delete distributeTask;
	delete Distribute_Mutex;


	//for(unsigned i=0;i<threads.size();i++){
		//threads.at(i)->Terminate();
	//}
	while(!task_q.empty()){
		if(task_q.front()->AutoTerminate()){
			delete task_q.front();
		}
		task_q.pop();
	}
}
void ThreadPool::Terminate(){
	distributeTask->Terminate();
	while(!ready_q.empty()){
		thread_terminate(ready_q.front());
		ready_q.pop();
	}

}
void ThreadPool::thread_terminate(Thread* thread){
	if(threads.size()==1){
		delete this;
	}else{//remove this thread if this is not last thread
		for(unsigned i=0;i<threads.size();i++){
			if(threads.at(i)==thread){
				threads.at(i)=threads.back();
				threads.pop_back();
				break;
			}
		}
	}
	thread->Terminate();
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
		task_q.pop();
	}else{
		ready_q.push(thread);
	}
	Distribute_Mutex->release();
}
} /* namespace Tim */
