#ifndef SOURCE_CLASS_TIM_OBJECTPOOL_OBJECTPOOLTEST_H_
#define SOURCE_CLASS_TIM_OBJECTPOOL_OBJECTPOOLTEST_H_
#include <string>
#include <iostream>
#include "class/tim/objectpool/ObjectPool.h"
void object_pool_test(){
	Tim::ObjectPool<std::string> *pool=new Tim::ObjectPool<std::string>(10);
	Tim::Object<std::string> *ss[20];
	char buffer[10]="";
	//==================allocate test================
	for(int i=0;i<10;i++){
		ss[i]=pool->create();
		buffer[0]=i+'0';
		ss[i]->get()=std::string("test")+std::string(buffer);
	}
	//==================free Object test================
	for(int i=0;i<10;i++){
		std::cout<<ss[i]->get()<<std::endl;
		ss[i]->free_object();
	}
	//==================re allocate test================
	for(int i=0;i<10;i++){
		ss[i]=pool->create();
		buffer[0]=i+'0';
		ss[i]->get()=std::string("te")+std::string(buffer);
	}
	//==================free Object test================
	for(int i=0;i<10;i++){
		std::cout<<ss[i]->get()<<std::endl;
		ss[i]->free_object();
	}
	//==================allocate more object than capacity test================
	for(int i=0;i<20;i++){
		ss[i]=pool->create();
		buffer[0]=i+'0';
		ss[i]->get()=std::string("t")+std::string(buffer);
	}
	//==================free Object test================
	for(int i=0;i<20;i++){
		std::cout<<ss[i]->get()<<std::endl;
		ss[i]->free_object();
	}
}




#endif /* SOURCE_CLASS_TIM_OBJECTPOOL_OBJECTPOOLTEST_H_ */
