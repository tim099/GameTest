#ifndef SOURCE_CLASS_TIM_ARRAY_ARRAY3D_CPP_
#define SOURCE_CLASS_TIM_ARRAY_ARRAY3D_CPP_
#include "class/tim/array/Array3D.h"
namespace Tim {

template <class Type>
Array3D<Type>::Array3D(glm::ivec3 _size) {
	size=_size;
	arr=new Type[size.x*size.y*size.z];
}
template <class Type>
Array3D<Type>::~Array3D() {
	delete[] arr;
}

template <class Type>
Type& Array3D<Type>::get(const int &x,const int &y,const int &z){
	return arr[size.y*size.z*x+size.z*y+z];
}

} /* namespace Tim */
#endif /* SOURCE_CLASS_TIM_ARRAY_ARRAY3D_CPP_ */
