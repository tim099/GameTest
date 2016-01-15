#ifndef SOURCE_CLASS_TIM_OBJECTPOOL_OBJPOOLTEST_H_
#define SOURCE_CLASS_TIM_OBJECTPOOL_OBJPOOLTEST_H_
#include <iostream>
#include <string>
#include "class/tim/objectpool/ObjPool.h"
void obj_pool_test(){
	Tim::ObjPool<std::string>*pool=new Tim::ObjPool<std::string>(10);
	std::string* ss[20];
	char buffer[10]="";
	//==================allocate test================
	for(int i=0;i<10;i++){
		ss[i]=pool->create();
		buffer[0]=i+'0';
		*ss[i]=std::string("test")+std::string(buffer);
	}
	//==================free Object test================
	for(int i=0;i<10;i++){
		std::cout<<*ss[i]<<std::endl;
		pool->free(ss[i]);
	}
	//==================re allocate test================
	for(int i=0;i<10;i++){
		ss[i]=pool->create();
		buffer[0]=i+'0';
		*ss[i]=std::string("test")+std::string(buffer);
	}
	//==================free Object test================
	for(int i=0;i<10;i++){
		std::cout<<*ss[i]<<std::endl;
		pool->free(ss[i]);
	}
	//==================allocate more object than capacity test================
	for(int i=0;i<20;i++){
		ss[i]=pool->create();
		buffer[0]=i+'0';
		*ss[i]=std::string("test")+std::string(buffer);
	}
	//==================free Object test================
	for(int i=0;i<20;i++){
		std::cout<<*ss[i]<<std::endl;
		pool->free(ss[i]);
	}
}



#endif /* SOURCE_CLASS_TIM_OBJECTPOOL_OBJPOOLTEST_H_ */
