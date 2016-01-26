#ifndef SOURCE_CLASS_TIM_OBJECTPOOL_OBJECTPOOL_CPP_
#define SOURCE_CLASS_TIM_OBJECTPOOL_OBJECTPOOL_CPP_

#include "class/tim/objectpool/ObjectPool.h"
#include "class/tim/array/Array.h"
#include <iostream>
#include <cstring>

namespace Tim {
template <class Type>
ObjectPool<Type>* ObjectPool<Type>::cur_pool=0;
template <class Type>
ObjectPool<Type>::ObjectPool(unsigned size,bool _dynamic_malloc) {
	dynamic_malloc=_dynamic_malloc;
	prev_create=0;
	create_obj(size);
	cur_pool=this;
}
template <class Type>
ObjectPool<Type>::~ObjectPool() {
	for(unsigned i=0;i<objs.size();i++){
		delete objs.at(i);
	}
}
template <class Type>
void ObjectPool<Type>::create_obj(unsigned size){
	objs.reserve(size);
	while(objs.size()<size){
		objs.push_back(new Object<Type>());
	}
}
template <class Type>
Object<Type>* ObjectPool<Type>::create(){
	for(unsigned i=prev_create;i<objs.size();i++){
		if(!objs[i]->in_used){
			objs[i]->in_used=true;
			prev_create=i;
			return (objs[i]);
		}
	}
	for(unsigned i=0;i<prev_create;i++){
		if(!objs[i]->in_used){
			objs[i]->in_used=true;
			prev_create=i;
			return (objs[i]);
		}
	}
	if(dynamic_malloc){
		create_obj(2*objs.size()+1);
		return create();
	}else{
		std::cerr<<"Tim::ObjectPool bad alloc, make sure you initialize with enough size"<<std::endl;
		std::cerr<<"or you can enable dynamic_malloc"<<std::endl;
		return 0;
	}

}

} /* namespace Tim */

#endif /* SOURCE_CLASS_TIM_OBJECTPOOL_OBJECTPOOL_CPP_ */
