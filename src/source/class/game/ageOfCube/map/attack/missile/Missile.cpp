#include "class/game/ageOfCube/map/attack/missile/Missile.h"
#include "class/display/draw/drawObject/AllDrawObjects.h"
#include "class/audio/AudioController.h"
#include "class/game/ageOfCube/map/unit/Unit.h"

namespace AOC {
void Missile::attack_pre_init(){

}
Missile::Missile() {
	radius=0.1;
	timer=0;
	type=0;
}
Missile::Missile(Missile* missile){
	radius=missile->radius;
	timer=0;
	type=0;
}
Missile::~Missile() {

}
void Missile::save_attack(FILE* file){
	fprintf(file,"%d %d\n",timer,type);
}
void Missile::load_attack(FILE* file){
	fscanf(file,"%d %d\n",&timer,&type);
}
void Missile::collide_action(RigidBody* b){

}
void  Missile::explode(){
	//std::cout<<"Missile::explode()"<<std::endl;
	for(unsigned i=0;i<collied_units.size();i++){
		collied_units.at(i)->hp_alter(-damage);
	}
	Audio::AudioController::get_cur_object()->
			play_by_dis("default_sound_effect/Bomb.wav",pos,200);
	die=true;
}
void Missile::draw_attack(){
	//std::cout<<"Missile::draw_attack()"<<std::endl;
	///*
	Display::DrawObject *missile_Drawobj=Display::AllDrawObjects::get_cur_object()->get("attack/missile_3");
	math::Position *dp_pos=new math::Position();
	dp_pos->set_pos(glm::vec3(pos.x,pos.y,pos.z));
	dp_pos->set_scale(glm::vec3(2*radius,2*radius,2*radius));
	missile_Drawobj->push_temp_drawdata(new Display::DrawDataObj(dp_pos,true,true));
	//*/
}
void Missile::attack_update(){
	//std::cout<<"Missile::attack_update()"<<std::endl;
	timer++;
	if(timer>300)die=true;
	if(be_collided||collided){
		explode();
	}
	if(target){
		vel*=0.75;
		if(timer<30){
			vel.y+=0.045;
		}else{
			math::vec3<double> target_pos=target->get_mid_pos();
			math::vec3<double> del_pos=target_pos-pos;
			math::vec3<double> del_pos_xz=del_pos;
			del_pos_xz.y=0;
			if(del_pos_xz.get_length()<1.0){
				vel+=0.045*del_pos.normalize();
			}else{
				vel+=0.045*del_pos_xz.normalize();
			}
		}
	}else{
		//explode();
	}
}
} /* namespace AOC */
