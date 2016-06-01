#ifndef SOURCE_CLASS_TIM_POINTER_SMARTPOINTER_TEST_
#define SOURCE_CLASS_TIM_POINTER_SMARTPOINTER_TEST_
#include "class/tim/pointer/SmartPointer.h"
#include "class/tim/string/String.h"
#include "class/test/TestA.h"
#include <vector>
void smart_pointer_test(){
	///*
	{
		std::vector<Tim::SmartPointer<Tim::TestA> >tests;
		for(int i=0;i<10;i++){
			//std::cout<<"1"<<std::endl;
			Tim::SmartPointer<Tim::TestA> t(new Tim::TestA("test"+Tim::String::to_string(i)));
			//std::cout<<"2"<<std::endl;
			tests.push_back(t);
			//std::cout<<"3"<<std::endl;
			tests.at(i)->hi();
		}
	}
	//*/
	{
		Tim::SmartPointer<Tim::TestA> test0(new Tim::TestA("test0"));
		(*test0).hi();
	}

	{
	Tim::SmartPointer<Tim::TestA> test2;
	{
		Tim::SmartPointer<Tim::TestA> test(new Tim::TestA("test"));
		test->hi();
		test2=test;
		test=test2;
	}
	Tim::SmartPointer<Tim::TestA> test3(new Tim::TestA("test3"));
	test2->hi();
	test2=test3;
	test2->hi();
	}
}

#endif
