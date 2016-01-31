#ifndef SOURCE_CLASS_TIM_ARRAY_ARRAY2D_H_
#define SOURCE_CLASS_TIM_ARRAY_ARRAY2D_H_

namespace Tim {
template <class Type>
class Array2D {
public:
	Array2D(int sizex,int sizey);
	virtual ~Array2D();

	//will not check the bound!!used carefully
	inline Type& get(const int &x,const int &y){
		return arr[sizex*y+x];
	}
	int sizex;
	int sizey;
protected:
	Type* arr;
};

} /* namespace Tim */
#include "class/tim/array/Array2D.cpp"

#endif /* SOURCE_CLASS_TIM_ARRAY_ARRAY2D_H_ */
