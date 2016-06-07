#include "class/tim/math/Position.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/transform.hpp>
#include <iostream>
namespace math {
Position::Position() {
	init(glm::vec3(0, 0, 0), glm::vec3(0, 0, 0), 0);
}
Position::Position(const Position &p) {
	init(p.pos, p.r, p.parent_pos);
}
Position::Position(glm::vec3 _pos, glm::vec3 _r, Position *_parent_pos) {
	init(_pos, _r, _parent_pos);
}
Position::~Position() {
	//std::cout<<"Position::~Position()"<<std::endl;
}
void Position::set_r(glm::vec3 _r) {

	if(r.x!=_r.x)rotated_x = true;
	if(r.y!=_r.y)rotated_y = true;
	if(r.z!=_r.z)rotated_z = true;
	r = _r;
	updated = true;
}
void Position::set_ry(float ry) {
	r.y = ry;
	rotated_y = true;
	updated = true;
}
void Position::set_pos(glm::vec3 _pos) {
	pos = _pos;
	updated = true;
}
glm::vec3 Position::get_r() const {
	return r;
}
glm::vec3 Position::get_pos() const {
	return pos;
}
void Position::set_scale(glm::vec3 _scale){
	scale=_scale;
	updated = true;
}
void Position::init(const Position &p) {
	init(p.pos, p.r, p.parent_pos);
}
void Position::init(glm::vec3 _pos, glm::vec3 _r, Position *_parent_pos) {
	pos = _pos;
	r = _r;
	parent_pos = _parent_pos;
	updated = true;
	quat_x=glm::quat(1,0,0,0);
	quat_y=glm::quat(1,0,0,0);
	quat_z=glm::quat(1,0,0,0);
	if(r.x!=0){
		rotated_x = true;
	}else{
		rotated_x=false;
	}
	if(r.y!=0){
		rotated_y = true;
	}else{
		rotated_y=false;
	}
	if(r.z!=0){
		rotated_z = true;
	}else{
		rotated_z=false;
	}
	scale=glm::vec3(1,1,1);
}
glm::quat Position::get_quaternion(glm::vec3 axis, float angle) {
	//glm::vec3 axis=glm::normalize(_axis);
	float h_theta = angle * 0.5 * (M_PI / 180.0);
	float sin_h_theta = sinf(h_theta);
	return glm::quat( cosf(h_theta),axis.x * sin_h_theta, axis.y * sin_h_theta,
			axis.z * sin_h_theta);
}
glm::vec4 Position::multiply_quaternion(glm::vec4 a, glm::vec4 b) {
	return glm::vec4(b.w * a.x + b.x * a.w + b.y * a.z - b.z * a.y,
			b.w * a.y + b.y * a.w + b.z * a.x - b.x * a.z,
			b.w * a.z + b.z * a.w + b.x * a.y - b.y * a.x,
			b.w * a.w - b.x * a.x - b.y * a.y - b.z * a.z);
}
glm::mat4 Position::get_pos_mat() {
	if (!updated){
		if (parent_pos) {
			return parent_pos->get_pos_mat()*pos_matrix;
		}else{
			return pos_matrix;
		}
	}
	pos_matrix = glm::mat4(1.0f);


	if(pos!=glm::vec3(0,0,0)){
		pos_matrix *= glm::translate(pos);
	}

	if(rotated_x||rotated_y||rotated_z){
		glm::quat total;
		if (rotated_x) {
			quat_x = get_quaternion(glm::vec3(1, 0, 0), r.x);
			rotated_x=false;
		}
		if (rotated_y) {
			quat_y = get_quaternion(glm::vec3(0, 1, 0), r.y);
			//glm::mat4 rmat = glm::rotate(r.y, glm::vec3(0, 1, 0));
			rotated_y=false;
		}
		if (rotated_z) {
			quat_z = get_quaternion(glm::vec3(0, 0, 1), r.z);
			rotated_z=false;
		}
		r_mat=glm::mat4_cast(glm::cross(glm::cross(quat_y,quat_x),quat_z));
	}
	if(r.x!=0.0||r.y!=0.0||r.z!=0.0){
		pos_matrix *= r_mat;
	}
	if(scale!=glm::vec3(1,1,1)){
		pos_matrix *=glm::scale(scale);
	}

	updated = false;
	if (parent_pos) {
		return parent_pos->get_pos_mat()*pos_matrix;
	}else{
		return pos_matrix;
	}
}
}
