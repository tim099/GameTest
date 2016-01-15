#ifndef SOURCE_CLASS_TIM_OBJECTPOOL_OBJECT_H_
#define SOURCE_CLASS_TIM_OBJECTPOOL_OBJECT_H_

namespace Tim {
template <class Type>
class ObjectPool;

template <class Type>
class Object{
public:
	friend class ObjectPool<Type>;

	Object();
	virtual ~Object();
	Type& get();
	void free_object();

private:
	Type *obj;
	bool in_used;

};

} /* namespace Tim */
#include "class/tim/objectpool/Object.cpp"
#endif /* SOURCE_CLASS_TIM_OBJECTPOOL_OBJECT_H_ */
