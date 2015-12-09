#ifndef ARRAY_H_
#define ARRAY_H_
#include <algorithm>
namespace Tim {
template <class DataType>
class Array {
public:
	Array();
	virtual ~Array();
	static void size_alter(DataType *&arr,int len,int new_len){
		DataType* new_arr=new DataType[new_len];
		std::copy(arr,arr+len,new_arr);
		std::swap(arr,new_arr);
		delete new_arr;
	}
};

} /* namespace Tim */

#endif /* ARRAY_H_ */
