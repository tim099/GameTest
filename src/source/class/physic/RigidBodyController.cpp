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
bool RigidBodyController::detect_collision(RigidBody* a,bool stop_when_collide){
	RigidBody *b;
	bool collided=false;
	for(unsigned i=0;i<special_collisions.size();i++){
		b=special_collisions.at(i);
		if(b!=a){
			if(b->check_collision(a)){
				b->collide(a);
				a->be_collide(b);
				collided=true;
			}
		}
	}
	for(unsigned i=0;i<collisions.size();i++){
		b=collisions.at(i);
		if(b!=a){
			if(a->check_collision(b)){
				a->collide(b);
				b->be_collide(a);
				collided=true;
				if(stop_when_collide)break;
			}
		}
	}
	return collided;
}
void RigidBodyController::check_collision(){
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
			std::cout<<"fast colli seg="<<seg<<std::endl;
			body->pos=prev_pos;
			for(int i=1;i<=seg;i++){
				body->prev_pos=body->pos;
				body->pos=((seg-i)/(double)seg)*prev_pos+(i/(double)seg)*pos;
				if(detect_collision(body,true))break;

			}
		}else{
			detect_collision(body,true);
		}

	}
	collisions.clear();
	special_collisions.clear();
}
void RigidBodyController::update(){
	/*
	for(unsigned i=0;i<rigid_bodys.size();i++){
		rigid_bodys.at(i)->update_rigid_body();
	}
	*/
	check_collision();
}
} /* namespace physic */
