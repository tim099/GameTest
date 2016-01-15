#ifndef ARRAY_CPP_
#define ARRAY_CPP_
#include "class/tim/array/Array.h"

namespace Tim {
template <class DataType>
Array<DataType>::Array() {

}
template <class DataType>
Array<DataType>::~Array() {

}
template <class DataType>
void Array<DataType>::size_alter(DataType *&arr,int len,int new_len){
	DataType* new_arr=new DataType[new_len];
	std::copy(arr,arr+len,new_arr);
	std::swap(arr,new_arr);
	delete new_arr;
}
} /* namespace Tim */
#endif
