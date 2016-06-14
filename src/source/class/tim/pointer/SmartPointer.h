#ifndef SOURCE_CLASS_TIM_POINTER_SMARTPOINTER_H_
#define SOURCE_CLASS_TIM_POINTER_SMARTPOINTER_H_
#include <iostream>
#include "class/tim/thread/mutex/Mutex.h"
namespace Tim {
template <class Type>
class SmartPointer {
public:
	SmartPointer(){
		//std::cout<<"SmartPointer()"<<std::endl;
		ptr=0;
		pointed_num=0;
		mutex=0;
	}

	SmartPointer(Type *_ptr){
		//std::cout<<"SmartPointer(Type *_ptr)"<<std::endl;
		ptr=_ptr;
		pointed_num=new int(1);
		mutex=new Tim::Mutex();
	}
	SmartPointer(const SmartPointer &that){
		//std::cout<<"SmartPointer(const SmartPointer &that)"<<std::endl;
		ptr=0;
		pointed_num=0;
		mutex=0;
		*this=that;
	}
	virtual ~SmartPointer(){
		//std::cout<<"~SmartPointer()"<<std::endl;
		clear();
	}
	inline SmartPointer& operator=(const SmartPointer &that){
		if(this!=&that){
			clear();
			if(that.ptr){
				that.mutex->wait_for_this();
				ptr=that.ptr;
				mutex=that.mutex;
				pointed_num=that.pointed_num;
				(*pointed_num)++;
				that.mutex->release();
			}
		}
		return *this;
	}
	inline Type* operator->(){
		return ptr;
	}
	inline Type& operator*(){
		return *ptr;
	}
	inline Type* get(){
		return ptr;
	}
	inline void clear(){
		if(ptr){
			mutex->wait_for_this();
			--(*pointed_num);
			bool flag=false;
			if(*pointed_num==0)flag=true;//last ptr

			mutex->release();
			if(flag){
				delete pointed_num;
				delete ptr;
				delete mutex;
			}

			mutex=0;
			pointed_num=0;
			ptr=0;
		}
	}
protected:
	int* pointed_num;
	Type *ptr;
	Tim::Mutex *mutex;
};

} /* namespace Tim */
#include "class/tim/pointer/SmartPointer.cpp"
#endif /* SOURCE_CLASS_TIM_POINTER_SMARTPOINTER_H_ */
