#include "class/physic/RigidBodyController.h"

namespace physic {

RigidBodyController::RigidBodyController() {
	register_cur();
}
RigidBodyController::~RigidBodyController() {

}
void RigidBodyController::check_collision(RigidBody* a){
	RigidBody *b;
	for(unsigned i=0;i<collisions.size();i++){
		b=collisions.at(i);
		if(b!=a){
			if(a->check_collision(b)){
				a->collide(b);
				b->collide(a);
				break;
			}
		}
	}
}
void RigidBodyController::check_collision(){
	for(unsigned i=0;(i+1)<collisions.size();i++){
		check_collision(collisions.at(i));
	}
	for(unsigned i=0;i<special_collisions.size();i++){
		check_collision(special_collisions.at(i));
	}
	collisions.clear();
	special_collisions.clear();
}
void RigidBodyController::update(){
	for(unsigned i=0;i<rigid_bodys.size();i++){
		rigid_bodys.at(i)->update_rigid_body();
	}
	check_collision();
}
} /* namespace physic */
