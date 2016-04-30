#ifndef SOURCE_CLASS_TIM_ARRAY_VECTOR_H_
#define SOURCE_CLASS_TIM_ARRAY_VECTOR_H_
#include "class/tim/array/Array.h"
#include <iostream>
namespace Tim {
template <class Type>
class vector {
public:
	vector(){
		arr=0;
		cur_size=0;
		capacity=1;
		arr=new Type[capacity];
	}
	virtual ~vector(){
		delete[] arr;
	}
	inline Type& operator[] (unsigned i) {
		//std::cout<<"tim::vector Type& operator[] "<<std::endl;
		if(i>=cur_size){
			std::cerr<<"tim::vector [] out of range"<<std::endl;
			return arr[0];
		}
		return arr[i];
	}
	inline Type* at(unsigned i){
		std::cerr<<"tim::vector at"<<std::endl;
		if(i>=capacity){
			return 0;
		}
		return &arr[i];
	}
	inline void resize(unsigned i){
		//if(i<cur_size){
			//return;
		//}
		Array<Type>::size_alter(arr,cur_size,i);
		capacity=i;
	}
	inline unsigned size()const{
		return cur_size;
	}
	inline void clear(){
		cur_size=0;
	}
	inline void push_back(const Type &type){
		//std::cout<<"tim::vector push_back "<<std::endl;
		if(cur_size>=capacity){
			resize(2*cur_size+1);
		}
		arr[cur_size++]=type;
	}
protected:
	Type *arr;
	unsigned cur_size,capacity;
};

} /* namespace Tim */
#include "class/tim/array/vector.cpp"
#endif /* SOURCE_CLASS_TIM_ARRAY_VECTOR_H_ */
