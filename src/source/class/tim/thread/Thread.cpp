#include "class/tim/thread/Thread.h"
#include <iostream>
namespace Tim {

Thread::Thread(int priority,Tim::ExecuteDone *_done) {
	end=false;
	terminate=false;
	threadhandle=CreateThread(NULL,0,Execute,this,CREATE_SUSPENDED,&ThreadID);
	//threadhandle=CreateThread(NULL,0,Execute,this,0,&ThreadID);
	thread_start=false;
	set_priority(priority);
	done=_done;
}
Thread::~Thread() {
	if(!terminate)std::cout<<"thread delete error not terminated yet!!"<<std::endl;
	//else std::cout<<"thread delete success!!"<<std::endl;
	//if(done)delete done; dont!!if done=thread pool

}
void Thread::Terminate(){
	end=true;
	if(DONE()){
		ResumeThread(threadhandle);//return to active state to terminate
	}
	endMutex.wait_for_this();
	endMutex.release();
}
void Thread::join(DWORD time){
	while(!thread_start&&!DONE());//waste time until thread_start

	threadMutex.wait_for_this();
	threadMutex.release();
}
void Thread::set_priority(int _priority){
	priority=_priority;
	bool flag=SetThreadPriority(threadhandle,priority);
	if(flag)std::cout<<"set thread priority fail"<<std::endl;
}
bool Thread::END()const{
	return end;
}
bool Thread::DONE()const{
	if(task_q.empty())return true;
	else return false;
}
void Thread::start(){
	if(DONE()){
		std::cout<<"Thread::start ,can't start because already done"<<std::endl;
		return;
	}

	ResumeThread(threadhandle);
	///*
	unsigned i=1,j=0;
	while(!thread_start&&!DONE()){
		i++;
		if(i%1000==0){
			j++;
			if(j>1000){
				std::cout<<"thread not start for:"<<j*i<<"loop of waiting"<<std::endl;
				j=0;
			}
			i=0;
			ResumeThread(threadhandle);
		}
	}
	//*/
}
void Thread::sleep(){
	thread_start=false;
	threadMutex.release();

	//may start at here causing problem so start func should avoid this
	SuspendThread(threadhandle);//dangerous because may start again before suspend!!
}
void Thread::ExecuteTask(){
	threadMutex.wait_for_this();
	thread_start=true;
	Tim::Task *task;
	bool AutoTerminate;
	while(!task_q.empty()){
		task=task_q.front();
		AutoTerminate=task_q.front()->AutoTerminate();
		task->Execute();
		task->Execute_done();
		if(AutoTerminate){
			delete task_q.front();
		}
		task_q.pop();
	}
	if(done)done->done(this);


	//std::cout<<"all task finish"<<std::endl;
}
void Thread::push_task(Task* task){
	task_q.push(task);
}
void Thread::Execute(){
	while(!END()){
		if(DONE()){
			sleep();
		}else{
			ExecuteTask();
		}
	}
	terminate=true;
}
DWORD WINAPI Thread::Execute(LPVOID lpParameter){

	Thread* thread=(Thread*)lpParameter;
	thread->endMutex.wait_for_this();
	//std::cout<<"Execute start"<<std::endl;
	thread->Execute();
	//std::cout<<"Execute end"<<std::endl;
	thread->endMutex.release();
	delete thread;
	return 0;
}


} /* namespace Tim */
