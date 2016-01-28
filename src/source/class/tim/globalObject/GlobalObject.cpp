#ifndef SOURCE_CLASS_TIM_GLOBALOBJECT_GLOBALOBJECT_CPP_
#define SOURCE_CLASS_TIM_GLOBALOBJECT_GLOBALOBJECT_CPP_
#include "class/tim/globalObject/GlobalObject.h"

namespace Tim {
template<class type>
type* GlobalObject<type>::cur_obj=0;
template<class type>
GlobalObject<type>::GlobalObject() {
	//register_cur(); dont register
}
template<class type>
GlobalObject<type>::~GlobalObject() {
	if(cur_obj==this)cur_obj=0;
}
template<class type>
void GlobalObject<type>::register_cur(){
	cur_obj=(type*)this;
}
template<class type>
type* GlobalObject<type>::get_cur_object(){
	return cur_obj;
}
} /* namespace Tim */
#endif
