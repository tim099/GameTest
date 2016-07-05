#include "class/physic/RigidBody.h"
#include "class/physic/RigidBodyController.h"
#include <iostream>
#include <cstdlib>
namespace physic {

RigidBody::RigidBody() {
	//std::cout<<"RigidBody::RigidBody()="<<this<<std::endl;
	radius=1.0;
	collision_off=false;
	be_collide_off=false;
	special_collide_off=false;
	stop_when_collide=true;
	collided=false;
	be_collided=false;
	mass=1.0;
}
RigidBody::~RigidBody() {
	//std::cout<<"RigidBody::~RigidBody()="<<this<<std::endl;
	//RigidBodyController::get_cur_object()->remove(this);
}
void RigidBody::save_rigid_body(FILE * file){
	fprintf(file,"%lf %lf %lf\n",vel.x,vel.y,vel.z);
	fprintf(file,"%lf %lf %lf\n",pos.x,pos.y,pos.z);
	fprintf(file,"%lf %lf %lf\n",prev_pos.x,prev_pos.y,prev_pos.z);
	fprintf(file,"%lf %lf %lf\n",rotate.x,rotate.y,rotate.z);
	fprintf(file,"%lf %lf\n",radius,mass);
}
void RigidBody::load_rigid_body(FILE * file){
	fscanf(file,"%lf %lf %lf\n",&vel.x,&vel.y,&vel.z);
	fscanf(file,"%lf %lf %lf\n",&pos.x,&pos.y,&pos.z);
	fscanf(file,"%lf %lf %lf\n",&prev_pos.x,&prev_pos.y,&prev_pos.z);
	fscanf(file,"%lf %lf %lf\n",&rotate.x,&rotate.y,&rotate.z);
	fscanf(file,"%lf %lf\n",&radius,&mass);
}
void RigidBody::set_detect_collision(){
	RigidBodyController::get_cur_object()->push_collision(this);
}
void RigidBody::set_detect_special_collision(){
	RigidBodyController::get_cur_object()->push_special_collision(this);
}
bool RigidBody::check_collision(RigidBody* b){
	if(math::vec3<double>(pos-b->pos).get_length()<=(radius+b->radius)){
		return true;
	}
	return false;
}
void RigidBody::collide(RigidBody* b){
	collided=true;
	if(b->id)collided_id.push_back(b->id);
	collide_action(b);
}
void RigidBody::be_collide(RigidBody* b){
	be_collided=true;
	if(b->id)be_collided_id.push_back(b->id);
	be_collide_action(b);
}
void RigidBody::collide_action(RigidBody* b){
	math::vec3<double> o_pos=0.5*(b->pos+pos);
	math::vec3<double> o_v=(mass*vel+b->mass*b->vel)/(mass+b->mass);

	vel-=2.0*math::vec3<double>::normalize(pos-o_pos)*
			((vel-o_v).dot(math::vec3<double>::normalize(pos-o_pos)));
	b->vel-=2.0*math::vec3<double>::normalize(b->pos-o_pos)*
			((b->vel-o_v).dot(math::vec3<double>::normalize(b->pos-o_pos)));
	///*
	static const int range=100;
	vel+=math::vec3<double>(0.01*((rand()%range)-range/2)/(double)range,
							0.01*((rand()%range)-range/2)/(double)range,
							0.01*((rand()%range)-range/2)/(double)range)*vel.get_length();

	b->vel+=math::vec3<double>(0.01*((rand()%range)-range/2)/(double)range,
							   0.01*((rand()%range)-range/2)/(double)range,
							   0.01*((rand()%range)-range/2)/(double)range)*b->vel.get_length();
	//*/
	bool stuck=true;
	for(int i=0;i<4;i++){
		pos=0.5*(prev_pos+pos);
		if(!RigidBodyController::get_cur_object()->check_collision(this)){
			stuck=false;
			break;
		}
	}
	if(stuck){
		pos=prev_pos;
		///*
		if(RigidBodyController::get_cur_object()->check_collision(this)){//handle stuck
			math::vec3<double> vec=math::vec3<double>::normalize(
					((pos-o_pos)+radius*math::vec3<double>(0.000,0.001,0.000)));
			pos=o_pos+(1.01*radius)*vec;
			b->pos=o_pos-(1.01*b->radius)*vec;

		}
		//*/
	}
}
void RigidBody::be_collide_action(RigidBody* b){

}
void RigidBody::clear_collision_data(){
	collided=false;
	be_collided=false;
	collided_id.clear();
	be_collided_id.clear();
}
void RigidBody::update_rigid_body(){
	prev_pos=pos;
	pos+=vel;
}
} /* namespace physic */
