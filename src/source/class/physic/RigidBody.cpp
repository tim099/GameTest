#include "class/physic/RigidBody.h"
#include "class/physic/RigidBodyController.h"
namespace physic {

RigidBody::RigidBody() {
	RigidBodyController::get_cur_object()->push(this);
	size=1.0;
}
RigidBody::~RigidBody() {
	RigidBodyController::get_cur_object()->remove(this);
}
void RigidBody::save(FILE * file){
	fprintf(file,"%lf %lf %lf\n",acc.x,acc.y,acc.z);
	fprintf(file,"%lf %lf %lf\n",vel.x,vel.y,vel.z);
	fprintf(file,"%lf %lf %lf\n",pos.x,pos.y,pos.z);
	fprintf(file,"%lf\n",size);
}
void RigidBody::load(FILE * file){
	fscanf(file,"%lf %lf %lf\n",&acc.x,&acc.y,&acc.z);
	fscanf(file,"%lf %lf %lf\n",&vel.x,&vel.y,&vel.z);
	fscanf(file,"%lf %lf %lf\n",&pos.x,&pos.y,&pos.z);
	fscanf(file,"%lf\n",&size);
}
void RigidBody::set_detect_collision(){
	RigidBodyController::get_cur_object()->push_collision(this);
}
void RigidBody::set_detect_special_collision(){
	RigidBodyController::get_cur_object()->push_special_collision(this);
}
bool RigidBody::check_collision(RigidBody* b){
	if(math::vec3<double>(pos-b->pos).length()<=(size+b->size)){
		return true;
	}
	return false;
}
void RigidBody::collide(RigidBody* b){

}
void RigidBody::update_rigid_body(){
	vel+=acc;
	pos+=vel;
}
} /* namespace physic */
