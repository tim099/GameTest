#ifndef SOURCE_CLASS_TIM_MATH_VEC2_H_
#define SOURCE_CLASS_TIM_MATH_VEC2_H_
#include "glm/detail/precision.hpp"

namespace glm{
namespace detail{
template <typename T, precision P> struct tvec2;
}
typedef detail::tvec2<float, highp> highp_vec2;
typedef highp_vec2 vec2;
}

namespace math {
template <class Type>
class vec2 {
public:
	vec2(){
		x=0;y=0;
	}
	vec2(Type _x,Type _y){
		x=_x;y=_y;
	}
	vec2(vec2 const &vec){
		x=vec.x;y=vec.y;
	}
	vec2(glm::vec2 vec);
	static glm::vec2 convert(const vec2 &vec);
	virtual ~vec2(){

	}
	inline bool operator==(const vec2& vec){
		return (x==vec.x&&y==vec.y);
	}

	inline vec2& operator=(const vec2& vec){
		x=vec.x;y=vec.y;
		return *this;
	}
	inline vec2& operator+=(const vec2& vec){
		x+=vec.x;y+=vec.y;
		return *this;
	}
	inline vec2& operator-=(const vec2& vec){
		x-=vec.x;y-=vec.y;
		return *this;
	}
	inline vec2 operator+(const vec2& vec)const{
		return vec2(x+vec.x,y+vec.y);
	}
	inline vec2 operator-(const vec2& vec)const{
		return vec2(x-vec.x,y-vec.y);
	}
	inline vec2 operator*(const vec2& vec)const{
		return vec2(x*vec.x,y*vec.y);
	}
	inline vec2 operator*(const float& val)const{
		return vec2(x*val,y*val);
	}

	inline vec2 operator/(const vec2& vec)const{
		return vec2(x/vec.x,y/vec.y);
	}
	Type x,y;
};
template <class Type>
inline vec2<Type> operator*(const float& val,const vec2<Type> &vec){
	return vec*val;
}
} /* namespace Math */
#include "class/tim/math/vec2.cpp"
#endif /* SOURCE_CLASS_TIM_MATH_VEC2_H_ */
