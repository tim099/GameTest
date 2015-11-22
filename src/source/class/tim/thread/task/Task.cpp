#include "class/tim/Thread/task/Task.h"
#include <iostream>
namespace Tim {

Task::Task() {
	done=false;
	auto_terminate=false;
}
Task::~Task() {

}
bool Task::AutoTerminate()const{
	return auto_terminate;
}
void Task::Execute(){
	ExecuteTask();
	TaskDone();
	//done=true; //done by thread!!
}
bool Task::Done()const{
	return done;
}
void Task::TaskDone(){

}
} /* namespace Tim */
