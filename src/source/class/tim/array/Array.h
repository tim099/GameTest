#ifndef ARRAY_H_
#define ARRAY_H_
#include <algorithm>
namespace Tim {
template <class DataType>
class Array {
public:
	Array();
	virtual ~Array();
	static void size_alter(DataType *&arr,int len,int new_len);
};

} /* namespace Tim */
#include "class/tim/array/Array.cpp"
#endif /* ARRAY_H_ */
