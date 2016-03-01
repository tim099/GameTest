#ifndef SOURCE_CLASS_TIM_GLOBALOBJECT_SINGLETON_H_
#define SOURCE_CLASS_TIM_GLOBALOBJECT_SINGLETON_H_

namespace Tim {
template<class type>
class Singleton {
public:
	Singleton(){

	}
	virtual ~Singleton(){

	}
	static type* get_cur_object(){
		static type obj;
		return &obj;
	}
};

} /* namespace Tim */

#endif /* SOURCE_CLASS_TIM_GLOBALOBJECT_SINGLETON_H_ */
