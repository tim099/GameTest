#include "class/tim/thread/Thread.h"
#include <iostream>
namespace Tim {

Thread::Thread(int priority,Tim::ExecuteDone *_done) {
	end=false;
	terminate=false;
	threadhandle=CreateThread(NULL,0,Execute,this,CREATE_SUSPENDED,&ThreadID);
	//threadhandle=CreateThread(NULL,0,Execute,this,0,&ThreadID);
	threadMutex=new Mutex();
	thread_start=false;
	set_priority(priority);
	done=_done;
}
Thread::~Thread() {
	if(!terminate)std::cout<<"thread delete error not terminated yet!!"<<std::endl;
	else std::cout<<"thread delete success!!"<<std::endl;
	delete threadMutex;
	//if(done)delete done; dont!!if done=thread pool

}
void Thread::Terminate(){
	end=true;
	if(DONE())ResumeThread(threadhandle);//to return
}
void Thread::wait_for_this(DWORD time){
	while(!thread_start);

	threadMutex->wait_for_this();
	threadMutex->release();
}
void Thread::set_priority(int priority){
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
		std::cout<<"can't start already done"<<std::endl;
		return;
	}

	ResumeThread(threadhandle);
	int i=1;
	while(!thread_start){
		i++;
		if(i%1000==0){
			std::cout<<"thread not start"<<i<<std::endl;
			ResumeThread(threadhandle);
		}
	}
}
bool Thread::Suspended()const{
	///*
	DWORD val;
	if((val=WaitForSingleObject(threadhandle,0))==WAIT_ABANDONED){
		std::cout<<"cur suspended"<<std::endl;
		//ReleaseMutex(threadhandle);
		return true;
	}else{
		std::cout<<"not suspended:"<<val<<std::endl;
		//ReleaseMutex(threadhandle);
		return false;
	}
	//*/

}
void Thread::sleep(){
	//std::cout<<"wait"<<std::endl;
	thread_start=false;
	threadMutex->release();
	//may start at here causing problem
	SuspendThread(threadhandle);//dangerous because may start again before suspend!!
}
void Thread::ExecuteTask(){
	threadMutex->wait_for_this();
	thread_start=true;

	while(!task_q.empty()){
		task_q.front()->Execute();
		task_q.front()->done=true;//delete task_q.front(); dont!!
		if(task_q.front()->AutoTerminate())delete task_q.front();
		task_q.pop();
	}
	if(done)done->done(this);


	//std::cout<<"all task finish"<<std::endl;
}
void Thread::push_task(Task* task){
	task_q.push(task);
}
DWORD WINAPI Thread::Execute(LPVOID lpParameter){
	Thread* thread=(Thread*)lpParameter;
	//std::cout<<"Execute start"<<std::endl;
	while(!thread->END()){
		if(thread->DONE()){
			thread->sleep();
		}else{
			thread->ExecuteTask();
		}
	}
	//std::cout<<"Execute end"<<std::endl;
	thread->terminate=true;
	delete thread;
	return 0;
}


} /* namespace Tim */
