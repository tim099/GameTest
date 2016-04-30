#ifndef SOURCE_CLASS_TIM_MATH_VEC2_H_
#define SOURCE_CLASS_TIM_MATH_VEC2_H_

namespace Math {
template <class Type>
class vec2 {
public:
	vec2(Type _x,Type _y){
		x=_x;y=_y;
	}
	virtual ~vec2();
	Type x,y;
};

} /* namespace Math */
#include "class/tim/math/vec2.cpp"
#endif /* SOURCE_CLASS_TIM_MATH_VEC2_H_ */
