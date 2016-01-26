#ifndef SOURCE_CLASS_TIM_OBJECTPOOL_OBJECTPOOL_H_
#define SOURCE_CLASS_TIM_OBJECTPOOL_OBJECTPOOL_H_
#include <vector>
#include "class/tim/objectpool/Object.h"
namespace Tim {
template <class Type>
class ObjectPool {

	static ObjectPool<Type>* cur_pool;
public:
	/*size is the max capacity of this Object pool
	 * enable dynamic_malloc will auto malloc more object when there is no any more free object
	 * after using object,call Object function free_obj to set this object available again
	 */
	ObjectPool(unsigned size=1,bool dynamic_malloc=true);
	virtual ~ObjectPool();
	Object<Type>* create();
protected:
	void create_obj(unsigned size);
	std::vector< Object<Type>* > objs;
	int prev_create;
	bool dynamic_malloc;
};

} /* namespace Tim */
#include "class/tim/objectpool/ObjectPool.cpp"
#endif /* SOURCE_CLASS_TIM_OBJECTPOOL_OBJECTPOOL_H_ */
