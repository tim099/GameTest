#include "class/tim/array/Array2D.h"
#ifndef SOURCE_CLASS_TIM_ARRAY_ARRAY2D_CPP_
#define SOURCE_CLASS_TIM_ARRAY_ARRAY2D_CPP_
namespace Tim {
template <class Type>
Array2D<Type>::Array2D(int _sizex,int _sizey) {
	sizex=_sizex;
	sizey=_sizey;
	arr=new Type[sizex*sizey];
}
template <class Type>
Array2D<Type>::~Array2D() {
	delete[] arr;
}

} /* namespace Tim */
#endif
