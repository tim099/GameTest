#include "class/physic/RigidBodyController.h"
#include <iostream>
namespace physic {

RigidBodyController::RigidBodyController() {
	register_cur();
}
RigidBodyController::~RigidBodyController() {

}
bool RigidBodyController::check_collision(RigidBody* a){
	RigidBody *b;
	for(unsigned i=0;i<collisions.size();i++){
		b=collisions.at(i);
		if(b!=a){
			if(a->check_collision(b)){
				return true;
			}
		}
	}
	return false;
}
bool RigidBodyController::detect_collision(RigidBody* a){
	if(a->collision_off)return false;

	RigidBody *b;
	bool collided=false;
	if(!a->special_collide_off){
		for(unsigned i=0;i<special_collisions.size();i++){
			b=special_collisions.at(i);
			if(b!=a&&!b->collision_off){
				if(b->check_collision(a)){
					b->collide(a);
					a->be_collide(b);
					collided=true;
				}
			}
		}
	}
	for(unsigned i=0;i<collisions.size();i++){
		b=collisions.at(i);
		if(b!=a&&!b->collision_off&&!b->be_collide_off){
			//std::cout<<"a="<<a<<","<<"b="<<b<<std::endl;
			if(a->check_collision(b)){
				a->collide(b);
				b->be_collide(a);
				collided=true;
				if(a->stop_when_collide)break;
			}
		}
	}
	return collided;
}
void RigidBodyController::check_collision(){
	//std::cout<<"RigidBodyController::check_collision() 1"<<std::endl;
	RigidBody* body;
	math::vec3<double> pos,prev_pos;
	int seg;
	double dis,max_vel;
	for(unsigned i=0;i<collisions.size();i++){
		body=collisions.at(i);
		body->update_rigid_body();
		dis=(body->pos-body->prev_pos).get_length();
		//max_vel=body->radius;
		max_vel=0.1;
		if(dis>max_vel){//moving fast!!
			pos=body->pos,prev_pos=body->prev_pos;
			seg=ceil(dis/max_vel);
			//std::cout<<"fast colli seg="<<seg<<std::endl;
			body->pos=prev_pos;
			for(int i=1;i<=seg;i++){
				body->prev_pos=body->pos;
				body->pos=((seg-i)/(double)seg)*prev_pos+(i/(double)seg)*pos;
				if(detect_collision(body))break;

			}
		}else{
			detect_collision(body);
		}

	}
	//std::cout<<"RigidBodyController::check_collision() 2"<<std::endl;
	collisions.clear();
	special_collisions.clear();
}
void RigidBodyController::pre_update(){

}
void RigidBodyController::update(){
	for(unsigned i=0;i<collisions.size();i++){
		collisions.at(i)->clear_collision_data();
	}
	for(unsigned i=0;i<special_collisions.size();i++){
		special_collisions.at(i)->clear_collision_data();
	}
	check_collision();
}
} /* namespace physic */
