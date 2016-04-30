#ifndef SOURCE_CLASS_TIM_MATH_VEC4_H_
#define SOURCE_CLASS_TIM_MATH_VEC4_H_

namespace Math {
template <class Type>
class vec4 {
public:
	vec4(){

	}
	vec4(Type _x,Type _y,Type _z,Type _w){
		x=_x;y=_y;z=_z;w=_w;
	}

	virtual ~vec4(){

	}
	vec4& operator=(const vec4& vec){
		x=vec.x;y=vec.y;z=vec.z;w=vec.w;
		return *this;
	}
	Type x,y,z,w;
};

} /* namespace Math */
#include "class/tim/math/vec4.cpp"
#endif /* SOURCE_CLASS_TIM_MATH_VEC4_H_ */
