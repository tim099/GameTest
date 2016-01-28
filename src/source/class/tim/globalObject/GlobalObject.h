#ifndef SOURCE_CLASS_TIM_GLOBALOBJECT_GLOBALOBJECT_H_
#define SOURCE_CLASS_TIM_GLOBALOBJECT_GLOBALOBJECT_H_

namespace Tim {
template<class type>
class GlobalObject {
	static type* cur_obj;
public:
	GlobalObject();
	virtual ~GlobalObject();
	static type* get_cur_object();
	void register_cur();
};

} /* namespace Tim */
#include "class/tim/globalObject/GlobalObject.cpp"
#endif /* SOURCE_CLASS_TIM_GLOBALOBJECT_GLOBALOBJECT_H_ */
