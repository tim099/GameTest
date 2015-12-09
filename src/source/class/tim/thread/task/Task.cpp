#include "class/tim/Thread/task/Task.h"
#include <iostream>
namespace Tim {

Task::Task() {
	done=false;
	auto_terminate=false;
	task_start=false;
	taskMutex=new Mutex();
}
Task::~Task() {
	delete taskMutex;
}
bool Task::AutoTerminate()const{
	return auto_terminate;
}
void Task::wait_for_this(DWORD time){
	while(!task_start);
	taskMutex->wait_for_this(time);
	taskMutex->release();
}
void Task::Execute(){
	taskMutex->wait_for_this();
	task_start=true;

	ExecuteTask();
	TaskDone();
	taskMutex->release();
	//done=true; //done by thread!!
}
bool Task::Done()const{
	return done;
}
void Task::TaskDone(){

}
} /* namespace Tim */
