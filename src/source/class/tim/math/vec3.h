#ifndef SOURCE_CLASS_TIM_MATH_VEC3_H_
#define SOURCE_CLASS_TIM_MATH_VEC3_H_

namespace math {
template <class Type>
class vec3 {
public:
	vec3(){
		x=0;y=0;z=0;
	}
	vec3(Type _x,Type _y,Type _z){
		x=_x;y=_y;z=_z;
	}
	virtual ~vec3(){

	}
	inline bool operator==(const vec3& vec){
		return (x==vec.x&&y==vec.y&&z==vec.z);
	}
	inline vec3& operator=(const vec3& vec){
		x=vec.x;y=vec.y;z=vec.z;
		return *this;
	}
	inline vec3& operator+=(const vec3& vec){
		x+=vec.x;y+=vec.y;z+=vec.z;
		return *this;
	}
	inline vec3& operator-=(const vec3& vec){
		x-=vec.x;y-=vec.y;z-=vec.z;
		return *this;
	}
	inline vec3 operator+(const vec3& vec)const{
		return vec3(x+vec.x,y+vec.y,z+vec.z);
	}
	inline vec3 operator-(const vec3& vec)const{
		return vec3(x-vec.x,y-vec.y,z-vec.z);
	}
	inline vec3 operator*(const vec3& vec)const{
		return vec3(x*vec.x,y*vec.y,z*vec.z);
	}
	inline vec3 operator/(const vec3& vec)const{
		return vec3(x/vec.x,y/vec.y,z/vec.z);
	}
	Type x,y,z;
};
#include "class/tim/math/vec3.cpp"
} /* namespace math */

#endif /* SOURCE_CLASS_TIM_MATH_VEC3_H_ */
