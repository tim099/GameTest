#ifndef SOURCE_CLASS_TIM_MATH_VEC4_H_
#define SOURCE_CLASS_TIM_MATH_VEC4_H_

namespace math {
template <class Type>
class vec4 {
public:
	vec4(){
		x=0;y=0;z=0;w=0;
	}
	vec4(Type _x,Type _y,Type _z,Type _w){
		x=_x;y=_y;z=_z;w=_w;
	}

	virtual ~vec4(){

	}
	inline bool operator==(const vec4& vec){
		return (x==vec.x&&y==vec.y&&z==vec.z&&w=vec.w);
	}
	inline vec4& operator=(const vec4& vec){
		x=vec.x;y=vec.y;z=vec.z;w=vec.w;
		return *this;
	}
	inline vec4& operator+=(const vec4& vec){
		x+=vec.x;y+=vec.y;z+=vec.z;w+=vec.w;
		return *this;
	}
	inline vec4& operator-=(const vec4& vec){
		x-=vec.x;y-=vec.y;z-=vec.z;w-=vec.w;
		return *this;
	}
	inline vec4 operator+(const vec4& vec)const{
		return vec4(x+vec.x,y+vec.y,z+vec.z,w+vec.w);
	}
	inline vec4 operator-(const vec4& vec)const{
		return vec4(x-vec.x,y-vec.y,z-vec.z,w-vec.w);
	}
	inline vec4 operator*(const vec4& vec)const{
		return vec4(x*vec.x,y*vec.y,z*vec.z,w*vec.w);
	}
	inline vec4 operator/(const vec4& vec)const{
		return vec4(x/vec.x,y/vec.y,z/vec.z,w/vec.w);
	}
	Type x,y,z,w;
};
template <class Type>
inline vec4<Type> operator*(const float& val,const vec4<Type> &vec){
	return vec*val;
}
} /* namespace Math */
#include "class/tim/math/vec4.cpp"
#endif /* SOURCE_CLASS_TIM_MATH_VEC4_H_ */
