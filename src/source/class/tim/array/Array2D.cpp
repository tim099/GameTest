#include "class/tim/array/Array2D.h"
#include <cstring>
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
Array2D<Type>::Array2D(Array2D* arr2d) {
	sizex=arr2d->sizex;
	sizey=arr2d->sizey;
	arr=new Type[sizex*sizey];
	memcpy (arr,arr2d->arr,sizex*sizey*sizeof(Type));
}
template <class Type>
Array2D<Type>::~Array2D() {
	delete[] arr;
}
template <class Type>
bool Array2D<Type>::operator==(const Array2D<Type>& arr2){
	if(sizex!=arr2.sizex||sizey!=arr2.sizey)return false;
	for(unsigned i=0;i<sizex*sizey;i++){
		if(arr[i]!=arr2.arr[i])return false;
	}
	return true;
}
} /* namespace Tim */
#endif
