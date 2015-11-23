#include "class/tim/thread/Thread.h"
#include <iostream>
namespace Tim {

Thread::Thread(int priority,Tim::ExecuteDone *_done) {
	end=false;
	terminate=false;
	threadhandle=CreateThread(NULL,0,Execute,this,CREATE_SUSPENDED,&ThreadID);
	//threadhandle=CreateThread(NULL,0,Execute,this,0,&ThreadID);
	set_priority(priority);
	done=_done;
}
Thread::~Thread() {
	if(!terminate)std::cout<<"thread delete error not terminated yet!!"<<std::endl;
	else std::cout<<"thread delete success!!"<<std::endl;
	//if(done)delete done; dont!!if done=thread pool
	//shoult terminate before delete!!
}
void Thread::Terminate(){
	end=true;
	if(DONE())ResumeThread(threadhandle);//to return
}
void Thread::wait_for_this(DWORD time){

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
		std::cout<<"can't join already done"<<std::endl;
		return;
	}
	ResumeThread(threadhandle);
}
void Thread::wait(){
	//std::cout<<"wait"<<std::endl;
	SuspendThread(threadhandle);
}
void Thread::ExecuteTask(){
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
			thread->wait();
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
