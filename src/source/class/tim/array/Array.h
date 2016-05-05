#ifndef ARRAY_H_
#define ARRAY_H_
#include <algorithm>
namespace Tim {
template <class Type>
class Array {
public:
	inline static void size_alter(Type *&arr,unsigned len,unsigned new_len){
		Type* new_arr=new Type[new_len];
		std::copy(arr,arr+len,new_arr);
		delete[] arr;
		arr=new_arr;
		//std::swap(arr,new_arr);
		//delete new_arr;
	}
	Array(int _size){
		size=_size;
		arr=new Type[size];
	}
	virtual ~Array(){
		delete[] arr;
	}
	inline Type& get(const unsigned &x){
		return arr[x];
	}

	unsigned size;
protected:
	Type* arr;
};

} /* namespace Tim */
#include "class/tim/array/Array.cpp"
#endif /* ARRAY_H_ */
