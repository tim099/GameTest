#include "class/test/TestTask.h"
#include <iostream>
TestTask::TestTask() {
	auto_terminate=true;
}
TestTask::~TestTask() {
	std::cout<<"test terminate"<<std::endl;
}
void TestTask::ExecuteTask(){
	volatile int l=0;
	for(unsigned long long i=0;i<3000000;i++){
			l++;
	}
}
