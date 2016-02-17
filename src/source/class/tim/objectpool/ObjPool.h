#ifndef SOURCE_CLASS_TIM_OBJECTPOOL_OBJPOOL_H_
#define SOURCE_CLASS_TIM_OBJECTPOOL_OBJPOOL_H_
#include <vector>
#include <queue>
#include "class/tim/globalObject/GlobalObject.h"
/*
 * another version of ObjectPool provide better efficiency but require to free obj after used
 * please keep only one copy if want to use static free and create
 */
namespace Tim {
template <class Type>
class ObjPool : public GlobalObject<ObjPool<Type> >{
	static ObjPool<Type>* cur_pool;
public:
	ObjPool(unsigned size);
	virtual ~ObjPool();
	static Type* mycreate();
	Type* create();
	static void myfree(Type* obj);
	void free(Type* obj);
private:
	void create_obj(unsigned size);
	std::vector<Type*>objs;
	std::queue<Type*>available_q;
};

} /* namespace Tim */
#include "class/tim/objectpool/ObjPool.cpp"
#endif /* SOURCE_CLASS_TIM_OBJECTPOOL_OBJPOOL_H_ */
