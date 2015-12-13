#include "class/display/light/PointLight.h"
#include <glm/gtx/transform.hpp>
#include <iostream>
PointLight::PointLight(glm::vec3 _pos,glm::vec3 _color,bool _shadow) : Light(_shadow){
	pos=_pos;
	color=_color;//glm::normalize(_color);
}
PointLight::~PointLight() {

}
glm::mat4 PointLight::get_LVP(float aspect,int n)const{
	glm::mat4 P=glm::perspective(90.0f,aspect,0.01f,100.0f);
	glm::mat4 V;

	switch(n){
		case 0:
			V=glm::lookAt(glm::vec3(0,0,0),glm::vec3(-1,0,0),glm::vec3(0,1,0));
			break;
		case 1:
			V=glm::lookAt(glm::vec3(0,0,0),glm::vec3(1,0,0),glm::vec3(0,1,0));
			break;
		case 2:
			V=glm::lookAt(glm::vec3(0,0,0),glm::vec3(0,-1,0),glm::vec3(1,0,0));
			break;
		case 3:
			V=glm::lookAt(glm::vec3(0,0,0),glm::vec3(0,1,0),glm::vec3(0,0,1));
			break;
		case 4:
			V=glm::lookAt(glm::vec3(0,0,0),glm::vec3(0,0,-1),glm::vec3(0,1,0));
			break;
		case 5:
			V=glm::lookAt(glm::vec3(0,0,0),glm::vec3(0,0,1),glm::vec3(0,1,0));
			break;
	}
	glm::mat4 trans=glm::translate(-pos);
	glm::mat4 PLVP=P*V*trans;

	return PLVP;
}
glm::mat4 PointLight::sent_uniform(GLuint programID,float aspect,int n){
	glm::mat4 PLVP=get_LVP(aspect,n);
	glUniformMatrix4fv(glGetUniformLocation(programID,"LVP"),1,GL_FALSE,&(PLVP[0][0]));
	return PLVP;
}
