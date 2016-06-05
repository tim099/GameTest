#ifndef SOURCE_CLASS_TIM_OBJECTPOOL_OBJPOOL_H_
#define SOURCE_CLASS_TIM_OBJECTPOOL_OBJPOOL_H_
#include <vector>
#include <queue>
#include "class/tim/globalObject/GlobalObject.h"
#include <iostream>
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
	inline static Type* mycreate(){
		return cur_pool->create();
	}
	inline static void myfree(Type* obj){
		cur_pool->free(obj);
	}
	inline Type* create(){
		//mutex->wait_for_this();
		if(available.empty()){
			create_obj(2*objs.size()+1);
		}
		Type *buff=available.back();
		available.pop_back();
		//std::cout<<"Type* ObjPool<Type>::create():"<<
				//"cur size="<<objs.size()<<",available size="<<available_q.size()<<std::endl;
		//mutex->release();
		return buff;
	}

	inline void free(Type* obj){
		//mutex->wait_for_this();
		available.push_back(obj);
		//mutex->release();
		//std::cout<<"ObjPool<Type>::free(Type* obj),"
				//<<"cur size="<<objs.size()<<",available size="<<available_q.size()<<std::endl;
	}
private:
	inline void create_obj(unsigned size){
		//std::cout<<"create obj size:"<<size<<std::endl;
		Type *buff;
		while(size>objs.size()){
			buff=new Type();
			objs.push_back(buff);
			available.push_back(buff);
		}
	}
	//Tim::Mutex* mutex;
	std::vector<Type*>objs;
	std::vector<Type*>available;
};

} /* namespace Tim */
#include "class/tim/objectpool/ObjPool.cpp"
#endif /* SOURCE_CLASS_TIM_OBJECTPOOL_OBJPOOL_H_ */
