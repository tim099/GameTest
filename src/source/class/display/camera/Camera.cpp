#include "class/display/camera/Camera.h"
#include <glm/gtx/transform.hpp>
#include <cmath>
#include <iostream>
#include "class/tim/math/Math.h"
namespace Display{
Camera::Camera(glm::vec3 _pos,glm::vec3 _look_at,glm::vec3 _up,
		float _fovy,float _z_near,float _z_far){
	pos=_pos;look_at=_look_at;up=_up;fovy=_fovy;
	z_near=_z_near;z_far=_z_far;shadow_far=z_far;PSSM_split_num=0;
	dis_alter_v=0;
}
Camera::~Camera() {

}
Camera::Camera(Camera* camera){
	pos=camera->pos;look_at=camera->look_at;up=camera->up;fovy=camera->fovy;
	z_near=camera->z_near;z_far=camera->z_far;shadow_far=z_far;PSSM_split_num=0;
	dis_alter_v=camera->dis_alter_v;
}
glm::mat4 Camera::sent_uniform(GLuint programID,float aspect,std::string name){
	 glm::mat4 VP=view_matrix(aspect);
	 glUniform3f(glGetUniformLocation(programID,"camera_pos"),pos.x,pos.y,pos.z);
	 glUniformMatrix4fv(glGetUniformLocation(programID,name.c_str()),1,GL_FALSE,&(VP[0][0]));
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
void Camera::update(){
	dis_alter(dis_alter_v);
	dis_alter_v*=0.9;
	move(v);
	v*=0.9;
}

void Camera::gen_PSSM_AABB(int split_num, float aspect){
	std::vector<float> PSSM_split_points;
	float c_log, c_uni, c_ratio=0.5;

	PSSM_AABBs.clear();

	PSSM_split_points.push_back(z_near);
	for(int i=1; i<=split_num; i++){
		c_log = z_near*glm::pow((shadow_far/z_near),(float)i/(float)split_num);
		c_uni = z_near + (shadow_far-z_near)*(float)i/(float)split_num;
		PSSM_split_points.push_back(c_ratio*c_log + (1.0f-c_ratio)*c_uni);
	}//find the distance

	glm::vec3 look_vector = glm::normalize(look_at - pos);
	glm::vec3 right_vector = glm::normalize(glm::cross(look_vector, up));
	glm::vec3 up_vector = glm::normalize(glm::cross(right_vector, look_vector));
	glm::vec3 AABB_point,AABB_min,AABB_max;
	float dis;
	static float up_dir[4] = {1.0,1.0,-1.0,-1.0};
	static float right_dir[4] = {1.0,-1.0,1.0,-1.0};

	//AABB_min = AABB_max = pos;
	//std::cout<<"AABB : "<<(AABB_min.x+AABB_max.x)/2<<","<<(AABB_min.x+AABB_max.x)/2<<","<<(AABB_min.x+AABB_max.x)/2<<std::endl;
	//PSSM_AABBs.push_back(Tim::AABB(AABB_max, AABB_min));

	for(int i=0; i<split_num; i++){
		AABB_min = AABB_max = pos+look_vector*PSSM_split_points[i];
		//std::cout<<"look_vec : "<<look_vector.x<<","<<look_vector.y<<","<<look_vector.z<<" PSSM_split_points : "<<PSSM_split_points[i]<<std::endl;
		for(int j=0; j<2; j++){
			dis = PSSM_split_points[i+j];
			for(int k=0; k<4; k++){
				AABB_point = pos+look_vector*dis;
				AABB_point = AABB_point + up_dir[k]*up_vector*dis*glm::tan(fovy/2);
				AABB_point = AABB_point + right_dir[k]*right_vector*dis*glm::tan(fovy/2)*aspect;
				AABB_min.x = glm::min(AABB_min.x, AABB_point.x);
				AABB_min.y = glm::min(AABB_min.y, AABB_point.y);
				AABB_min.z = glm::min(AABB_min.z, AABB_point.z);
				AABB_max.x = glm::max(AABB_max.x, AABB_point.x);
				AABB_max.y = glm::max(AABB_max.y, AABB_point.y);
				AABB_max.z = glm::max(AABB_max.z, AABB_point.z);
			}
		}
		//std::cout<<"AABB : "<<(AABB_min.x+AABB_max.x)/2<<","<<(AABB_min.y+AABB_max.y)/2<<","<<(AABB_min.z+AABB_max.z)/2<<std::endl;
		PSSM_AABBs.push_back(Tim::AABB(AABB_max, AABB_min));
	}
}

std::vector<Tim::AABB> *Camera::get_PSSM_AABBs(){
	return &PSSM_AABBs;
}

}
