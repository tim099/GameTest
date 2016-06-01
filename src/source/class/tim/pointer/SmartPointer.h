#ifndef SOURCE_CLASS_TIM_POINTER_SMARTPOINTER_H_
#define SOURCE_CLASS_TIM_POINTER_SMARTPOINTER_H_
#include <iostream>
namespace Tim {
template <class Type>
class SmartPointer {
	struct pair{

	};
public:
	SmartPointer(){
		//std::cout<<"SmartPointer()"<<std::endl;
		ptr=0;
		pointed_num=0;
	}

	SmartPointer(Type *_ptr){
		//std::cout<<"SmartPointer(Type *_ptr)"<<std::endl;
		ptr=_ptr;
		pointed_num=new int(1);
	}
	SmartPointer(const SmartPointer &that){
		//std::cout<<"SmartPointer(const SmartPointer &that)"<<std::endl;
		ptr=0;
		pointed_num=0;
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
				ptr=that.ptr;
				pointed_num=that.pointed_num;
				(*pointed_num)++;
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
		//std::cout<<"void clear()"<<std::endl;
		if(ptr){
			if(--(*pointed_num)==0){
				delete pointed_num;
				delete ptr;
			}
			pointed_num=0;
			ptr=0;
		}

	}
protected:
	int* pointed_num;
	Type *ptr;
};

} /* namespace Tim */
#include "class/tim/pointer/SmartPointer.cpp"
#endif /* SOURCE_CLASS_TIM_POINTER_SMARTPOINTER_H_ */
