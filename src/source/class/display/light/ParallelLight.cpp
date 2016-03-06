#include <class/display/light/ParallelLight.h>
#include <glm/gtx/transform.hpp>
#include <iostream>
ParallelLight::ParallelLight(glm::vec3 _vec,glm::vec3 _color,bool _shadow)
: Light(_shadow){
	vec=_vec;
	color=_color;
}
ParallelLight::~ParallelLight() {

}
glm::mat4 ParallelLight::get_LVP(float aspect,double size,glm::vec3 trans)const{
	glm::vec3 up_vec(0,1,0);
	if(vec==glm::vec3(0,-1,0)||vec==glm::vec3(0,1,0))up_vec=glm::vec3(0,1,0.0001);
	glm::mat4 view=glm::lookAt(glm::normalize(vec)+trans,trans,up_vec);
	glm::mat4 LVP=glm::scale(glm::vec3(size*0.12,size*0.12*aspect,0.007))*view;
	return LVP;
}
