#include <class/display/light/ParallelLight.h>
#include <glm/gtx/transform.hpp>
#include <iostream>
namespace Display{
ParallelLight::ParallelLight(glm::vec3 _vec,glm::vec3 _color,bool _shadow)
: Light(_shadow){
	vec=_vec;
	color=_color;
}
ParallelLight::~ParallelLight() {

}
glm::mat4 ParallelLight::get_LVP(float aspect,double size,glm::vec3 trans)const{
	glm::vec3 up_vec(0,1,0);
	//std::cout<<"ParallelLight vec : "<<vec.x<<","<<vec.y<<","<<vec.z<<std::endl;
	if(vec==glm::vec3(0,-1,0)||vec==glm::vec3(0,1,0))up_vec=glm::vec3(0,1,0.0001);
	glm::mat4 view=glm::lookAt(glm::normalize(vec)+trans,trans,up_vec);
	glm::mat4 LVP=glm::scale(glm::vec3(size*0.52,size*0.52*aspect,0.007))*view;
	return LVP;
}

glm::mat4 ParallelLight::get_PSSM_LVP(float aspect, double size, glm::vec3 trans, Tim::AABB PSSM_AABB){
	glm::vec3 up_vec(0,1,0);

	//std::cout<<"trans : "<<trans.x<<","<<trans.y<<","<<trans.z<<" size : "<<size<<std::endl;
	trans = (PSSM_AABB.max_pos + PSSM_AABB.min_pos)*0.5f;
	//std::cout<<"trans : "<<trans.x<<","<<trans.y<<","<<trans.z<<" size : "<<size<<std::endl;
	float LVP_scale = glm::length(PSSM_AABB.max_pos - PSSM_AABB.min_pos);
	//std::cout<<"ParallelLight vec : "<<vec.x<<","<<vec.y<<","<<vec.z<<" scale: "<<LVP_scale<<std::endl;

	if(vec==glm::vec3(0,-1,0)||vec==glm::vec3(0,1,0))up_vec=glm::vec3(0,1,0.0001);
	glm::mat4 view=glm::lookAt(glm::normalize(vec)+trans,trans,up_vec);
	//glm::mat4 LVP=glm::scale(glm::vec3(size*0.12,size*0.12*aspect,0.007))*view;
	glm::mat4 LVP=glm::scale(glm::vec3(15.0f/LVP_scale, 15.0f/LVP_scale*aspect, 1.0f/LVP_scale/*0.007*/))*view;

	return LVP;
}

}
