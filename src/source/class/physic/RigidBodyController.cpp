#include "class/physic/RigidBodyController.h"

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
void RigidBodyController::detect_collision(RigidBody* a,bool stop_when_collide){
	a->update_rigid_body();
	RigidBody *b;
	for(unsigned i=0;i<special_collisions.size();i++){
		b=special_collisions.at(i);
		if(b!=a){
			if(b->check_collision(a)){
				b->collide(a);
				a->be_collide(b);
			}
		}
	}
	for(unsigned i=0;i<collisions.size();i++){
		b=collisions.at(i);
		if(b!=a){
			if(a->check_collision(b)){
				a->collide(b);
				b->be_collide(a);
				if(stop_when_collide)break;
			}
		}
	}


}
void RigidBodyController::check_collision(){
	for(unsigned i=0;i<collisions.size();i++){
		detect_collision(collisions.at(i),true);
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
