#ifndef SOURCE_CLASS_TIM_OBJECTPOOL_OBJPOOL_CPP_
#define SOURCE_CLASS_TIM_OBJECTPOOL_OBJPOOL_CPP_
#include "class/tim/objectpool/ObjPool.h"

namespace Tim {
template <class Type>
ObjPool<Type>* ObjPool<Type>::cur_pool=0;
template <class Type>
ObjPool<Type>::ObjPool(unsigned size=2) {
	create_obj(size);
	cur_pool=this;
	//mutex=new Tim::Mutex();
}
template <class Type>
ObjPool<Type>::~ObjPool() {
	for(unsigned i=0;i<objs.size();i++){
		delete objs.at(i);
	}
	//delete mutex;
}



} /* namespace Tim */
#endif
