#ifndef SOURCE_CLASS_TIM_OBJECTPOOL_OBJECT_CPP_
#define SOURCE_CLASS_TIM_OBJECTPOOL_OBJECT_CPP_
#include "class/tim/objectpool/Object.h"

namespace Tim {
template <class Type>
Object<Type>::Object() {
	in_used=false;
	obj=new Type();
}
template <class Type>
Object<Type>::~Object() {
	delete obj;
}
template <class Type>
void Object<Type>::free_object(){
	in_used=false;
}
template <class Type>
Type& Object<Type>::get(){
	return *obj;
}
} /* namespace Tim */
#endif
