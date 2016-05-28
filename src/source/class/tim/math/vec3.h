#ifndef SOURCE_CLASS_TIM_MATH_VEC3_H_
#define SOURCE_CLASS_TIM_MATH_VEC3_H_
#include "glm/detail/precision.hpp"
#include <cmath>
namespace glm{
namespace detail{
template <typename T, precision P> struct tvec3;
}
typedef detail::tvec3<float, highp> highp_vec3;
typedef highp_vec3 vec3;
}
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
	inline double length()const{
		return sqrt(x*x+y*y+z*z);
	}
	inline bool operator==(const vec3& vec){
		return (x==vec.x&&y==vec.y&&z==vec.z);
	}
	inline bool operator>=(const vec3& vec){
		return (x>=vec.x&&y>=vec.y&&z>=vec.z);
	}
	inline bool operator<=(const vec3& vec){
		return (x<=vec.x&&y<=vec.y&&z<=vec.z);
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
template <class Type>
inline vec3<Type> operator*(const float& val,const vec3<Type> &vec){
	return vec*val;
}

} /* namespace math */
#include "class/tim/math/vec3.cpp"
#endif /* SOURCE_CLASS_TIM_MATH_VEC3_H_ */
