#ifndef SOURCE_CLASS_TIM_ARRAY_ARRAY3D_H_
#define SOURCE_CLASS_TIM_ARRAY_ARRAY3D_H_
#include <glm/glm.hpp>

namespace Tim {
template <class Type>
class Array3D {
public:
	Array3D(glm::ivec3 size);
	virtual ~Array3D();
	/*
	 * will not check the bound!!used carefully
	 */

	Type& get(const int &x,const int &y,const int &z);
	glm::ivec3 size;
	Type* arr;
};
} /* namespace Tim */
#include "class/tim/array/Array3D.cpp"
#endif /* SOURCE_CLASS_TIM_ARRAY_ARRAY3D_H_ */

