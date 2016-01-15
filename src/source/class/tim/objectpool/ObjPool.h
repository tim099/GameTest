#ifndef SOURCE_CLASS_TIM_OBJECTPOOL_OBJPOOL_H_
#define SOURCE_CLASS_TIM_OBJECTPOOL_OBJPOOL_H_
#include <vector>
#include <queue>
/*
 * another version of ObjectPool provide better efficiency but require to free obj after used
 *
 */
namespace Tim {
template <class Type>
class ObjPool {
public:
	ObjPool(unsigned size);
	virtual ~ObjPool();
	Type* create();
	void free(Type* obj);
private:
	void create_obj(unsigned size);
	std::vector<Type*>objs;
	std::queue<Type*>available_q;
};

} /* namespace Tim */
#include "class/tim/objectpool/ObjPool.cpp"
#endif /* SOURCE_CLASS_TIM_OBJECTPOOL_OBJPOOL_H_ */
