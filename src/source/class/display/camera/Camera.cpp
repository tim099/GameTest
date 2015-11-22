#include "class/display/camera/Camera.h"
#include <glm/gtx/transform.hpp>
#include <cmath>
#include <iostream>
#include "class/tim/math/Math.h"
Camera::Camera(glm::vec3 _pos,glm::vec3 _look_at,glm::vec3 _up,
		float _fovy,float _z_near,float _z_far){
	pos=_pos;look_at=_look_at;up=_up;fovy=_fovy;
	z_near=_z_near;z_far=_z_far;
	dis_alter_v=0;
}
Camera::~Camera() {

}
glm::mat4 Camera::sent_uniform(GLuint programID,float aspect){
	 glm::mat4 VP=view_matrix(aspect);
	 glUniform3f(glGetUniformLocation(programID,"camera_pos"),pos.x,pos.y,pos.z);
	 glUniformMatrix4fv(glGetUniformLocation(programID,"VP"),1,GL_FALSE,&(VP[0][0]));
	 return VP;
}
glm::mat4 Camera::view_matrix(float aspect){
	return perspective(aspect)*view();
}
glm::mat4 Camera::view()const{
	return glm::lookAt(pos,look_at,up);
}
glm::mat4 Camera::perspective(float aspect){
	return glm::perspective(fovy,aspect,z_near,z_far);
}
glm::vec3 Camera::look_vec()const{
	return glm::normalize(pos-look_at);
}
glm::vec3 Camera::look_vec_xz()const{
	return glm::normalize(glm::vec3(pos.x-look_at.x,0,pos.z-look_at.z));
}
float Camera::look_ry()const{
	glm::vec3 lv=look_vec();
	return atan2f(lv.x,lv.z)*(180/M_PI);
}
float Camera::look_dis()const{
	return glm::length(pos-look_at);
}
glm::vec3 Camera::yaw_vec()const{
	return glm::normalize(glm::cross(look_vec(),glm::vec3(0,1,0)));
}
void Camera::dis_alter(float dis){
	glm::vec3 vec(pos-look_at);
	if(dis<0&&fabs(dis)>glm::length(vec)-0.001){
		dis=-(glm::length(vec)-0.001);
	}
	if(glm::length(vec))vec*=(1.0/glm::length(vec));
	pos+=dis*vec;
}
void Camera::move_foward(float val){
	move(-look_vec_xz()*val);
}
void Camera::move_side(float val){
	move(glm::cross(look_vec_xz(),glm::vec3(0,1,0))*val);
}
void Camera::move(glm::vec3 del){
	look_at+=del;
	pos+=del;
}
void Camera::rotate(glm::vec3 v,float degrees){
	glm::vec4 vec(pos-look_at,0);
	glm::mat4 rmat=glm::rotate(degrees,v);
	vec=rmat*vec;
	pos=look_at+glm::vec3(vec);
}
void Camera::tic(){
	dis_alter(dis_alter_v);
	dis_alter_v*=0.9;
	move(vel);
	vel*=0.9;
}
