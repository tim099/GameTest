#ifndef SOURCE_CLASS_TIM_ARRAY_ARRAY3D_CPP_
#define SOURCE_CLASS_TIM_ARRAY_ARRAY3D_CPP_
#include "class/tim/array/Array3D.h"
namespace Tim {

template <class Type>
Array3D<Type>::Array3D(int _sizex,int _sizey,int _sizez) {
	sizex=_sizex;
	sizey=_sizey;
	sizez=_sizez;
	arr=new Type[sizex*sizey*sizez];
}
template <class Type>
Array3D<Type>::~Array3D() {
	delete[] arr;
}

template <class Type>
Type& Array3D<Type>::get(const int &x,const int &y,const int &z){
	return arr[sizey*sizez*x+sizez*y+z];
}

} /* namespace Tim */
#endif /* SOURCE_CLASS_TIM_ARRAY_ARRAY3D_CPP_ */
