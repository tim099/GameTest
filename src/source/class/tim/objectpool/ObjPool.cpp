#ifndef SOURCE_CLASS_TIM_OBJECTPOOL_OBJPOOL_CPP_
#define SOURCE_CLASS_TIM_OBJECTPOOL_OBJPOOL_CPP_
#include "class/tim/objectpool/ObjPool.h"
#include <iostream>
namespace Tim {
template <class Type>
ObjPool<Type>* ObjPool<Type>::cur_pool=0;
template <class Type>
ObjPool<Type>::ObjPool(unsigned size) {
	create_obj(size);
	cur_pool=this;
}
template <class Type>
ObjPool<Type>::~ObjPool() {
	for(unsigned i=0;i<objs.size();i++){
		delete objs.at(i);
	}
}
template <class Type>
void ObjPool<Type>::create_obj(unsigned size){
	Type *buff;
	while(size>objs.size()){
		buff=new Type();
		objs.push_back(buff);
		available_q.push(buff);
	}
}
template <class Type>
void ObjPool<Type>::myfree(Type* obj){
	cur_pool->free(obj);
}
template <class Type>
Type* ObjPool<Type>::mycreate(){
	return cur_pool->create();
}
template <class Type>
Type* ObjPool<Type>::create(){
	if(available_q.empty()){
		create_obj(2*objs.size()+1);
	}
	Type *buff=available_q.front();
	available_q.pop();
	//std::cout<<"cur size="<<objs.size()<<",available size="<<available_q.size()<<std::endl;
	return buff;
}
template <class Type>
void ObjPool<Type>::free(Type* obj){
	available_q.push(obj);
	//std::cout<<"cur size="<<objs.size()<<",available size="<<available_q.size()<<std::endl;
}
} /* namespace Tim */
#endif
