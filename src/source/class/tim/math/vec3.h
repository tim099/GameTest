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
	inline double get_length()const{
		return sqrt(x*x+y*y+z*z);
	}
	inline double dot(const vec3& vec)const{
		return (x*vec.x+y*vec.y+z*vec.z);
	}
	inline vec3 cross(const vec3& vec)const{
		return vec3(y*vec.z+z*vec.y,
				    x*vec.z+z*vec.x,
				    x*vec.y+y*vec.x);
	}
	inline void rotate_by_y(double degree){
		double angle=degree*(M_PI/180.0);
		double nx=x*cosf(angle)+z*sinf(angle);
		double nz=-x*sinf(angle)+z*cosf(angle);
		x=nx;z=nz;
	}
	static inline vec3 normalize(vec3 vec){
		double len=vec.get_length();
		if(len>0){
			vec.x/=len;vec.y/=len;vec.z/=len;
		}
		return vec;
	}
	inline vec3& normalize(){
		*this=normalize(*this);
		return *this;
	}
	inline bool operator==(const vec3& vec)const{
		return (x==vec.x&&y==vec.y&&z==vec.z);
	}
	inline bool operator>=(const vec3& vec)const{
		return (x>=vec.x&&y>=vec.y&&z>=vec.z);
	}
	inline bool operator<=(const vec3& vec)const{
		return (x<=vec.x&&y<=vec.y&&z<=vec.z);
	}
	inline bool operator>(const vec3& vec)const{
		return (x>vec.x&&y>vec.y&&z>vec.z);
	}
	inline bool operator<(const vec3& vec)const{
		return (x<vec.x&&y<vec.y&&z<vec.z);
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

	inline vec3 operator*(const double& val)const{
		return vec3(x*val,y*val,z*val);
	}
	inline vec3 operator/(const double& val)const{
		return vec3(x/val,y/val,z/val);
	}
	inline vec3 operator+(const double& val)const{
		return vec3(x+val,y+val,z+val);
	}
	inline vec3 operator-(const double& val)const{
		return vec3(x-val,y-val,z-val);
	}
	inline vec3 operator*=(const double& val){
		x*=val;y*=val;z*=val;
		return *this;
	}
	inline vec3 operator/=(const double& val){
		x/=val;y/=val;z/=val;
		return *this;
	}
	inline vec3 operator+=(const double& val){
		x+=val;y+=val;z+=val;
		return *this;
	}
	inline vec3 operator-=(const double& val){
		x-=val;y-=val;z-=val;
		return *this;
	}


	inline vec3 operator*(const int& val)const{
		return vec3(x*val,y*val,z*val);
	}
	inline vec3 operator/(const int& val)const{
		return vec3(x/val,y/val,z/val);
	}
	inline vec3 operator+(const int& val)const{
		return vec3(x+val,y+val,z+val);
	}
	inline vec3 operator-(const int& val)const{
		return vec3(x-val,y-val,z-val);
	}
	inline vec3 operator+=(const int& val){
		x+=val;y+=val;z+=val;
		return *this;
	}
	inline vec3 operator-=(const int& val){
		x-=val;y-=val;z-=val;
		return *this;
	}
	Type x,y,z;
};
template <class Type>
inline vec3<Type> operator*(const double& val,const vec3<Type> &vec){
	return vec*val;
}

template <class Type>
struct vec3Cmp{
	bool operator()(const vec3<Type>& v1, const vec3<Type>& v2) const{
		if(v1.x<v2.x){
			return true;
		}else if(v1.x==v2.x){
			if(v1.y<v2.y){
				return true;
			}else if(v1.y==v2.y){
				if(v1.z<v2.z){
					return true;
				}
			}
		}
		return false;
	}
};

} /* namespace math */
#include "class/tim/math/vec3.cpp"
#endif /* SOURCE_CLASS_TIM_MATH_VEC3_H_ */
