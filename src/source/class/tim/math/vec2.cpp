#ifndef SOURCE_CLASS_TIM_MATH_VEC2_CPP_
#define SOURCE_CLASS_TIM_MATH_VEC2_CPP_
#include "class/tim/math/vec2.h"
#include "glm/vec2.hpp"
namespace math {
template <class Type>
vec2<Type>::vec2(glm::vec2 vec){
	x=vec.x;y=vec.y;
}
template <class Type>
glm::vec2 vec2<Type>::convert(const vec2 &vec){
	return glm::vec2(vec.x,vec.y);
}

} /* namespace Math */
#endif /* SOURCE_CLASS_TIM_MATH_VEC2_CPP_ */
