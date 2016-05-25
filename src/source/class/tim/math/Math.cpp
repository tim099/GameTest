#include "class/tim/math/Math.h"

namespace Tim {

Math::Math() {


}
Math::~Math() {

}
float Math::fit_in_maxsize(math::vec2<float> size,math::vec2<float> maxsize){
	float alter=1.0;
	if(size.x>maxsize.x){
		alter=(maxsize.x/size.x);
	}
	if(size.y>maxsize.y){
		if((maxsize.y/size.y)<alter)alter=(maxsize.y/size.y);
	}
	return alter;
}
glm::vec2 Math::get_size(float width,float aspect){
	if (aspect > 0.999 && aspect < 1.001) {
		return glm::vec2(width, width);
	} else {
		return glm::vec2(width, width / aspect);
	}
}
glm::vec2 Math::max(glm::vec2 a,glm::vec2 b){
	return glm::vec2(Max(a.x,b.x),Max(a.y,b.y));
}
glm::vec2 Math::min(glm::vec2 a,glm::vec2 b){
	return glm::vec2(Min(a.x,b.x),Min(a.y,b.y));
}
int Math::pow(int base,int power){
	int sum=1;
	for(int i=0;i<power;i++){
		sum*=base;
	}
	return sum;
}
glm::mat4 Math::BiasMat(){
	glm::mat4 biasMat(
	0.5, 0.0, 0.0, 0.0,
	0.0, 0.5, 0.0, 0.0,
	0.0, 0.0, 0.5, 0.0,
	0.5, 0.5, 0.5, 1.0);
	return biasMat;
}
float Math::aspect(glm::ivec2 size){
	return ((float)size.x/(float)size.y);
}
float Math::aspect(math::vec2<int> size){
	return ((float)size.x/(float)size.y);
}
float Math::max(glm::vec3 v){
	if(v.x>v.y){
		if(v.x>v.z){
			return v.x;
		}else{
			return v.z;
		}
	}else{
		if(v.y>v.z){
			return v.y;
		}else{
			return v.z;
		}
	}
}
int Math::get_len(int val){
	int len=1;
	while(val>=10){
		val/=10;
		len++;
	}
	return len;
}
int Math::get_val_at(int val,int at){
	while(at>0){
		at--;
		val/=10;
	}
	return val%10;
}
glm::vec2 Math::convert_to_texcoord(glm::vec2 pos){
	return glm::vec2((pos.x+1.0)/2.0,(pos.y+1.0)/2.0);
}
glm::vec2 Math::convert_to_wincoord(glm::vec2 pos){
	return glm::vec2(pos.x*2.0-1.0,pos.y*2.0-1.0);
}

} /* namespace Tim */
