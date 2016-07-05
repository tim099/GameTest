#include "class/game/ageOfCube/map/attack/missile/Missile.h"
#include "class/display/draw/drawObject/AllDrawObjects.h"
#include "class/audio/AudioController.h"
#include "class/game/ageOfCube/map/unit/Unit.h"
#include "class/display/light/LightControl.h"
#include "class/display/draw/Draw.h"
#include <cmath>
namespace AOC {
void Missile::attack_pre_init(){

}
Missile::Missile() {
	radius=0.1;
	timer=0;
	type=0;
	explode_timer=0;
}
Missile::Missile(Missile* missile){
	radius=missile->radius;
	timer=missile->timer;
	type=missile->type;
	explode_timer=0;
}
Missile::~Missile() {

}
void Missile::save_attack(FILE* file){
	fprintf(file,"%d %d %d\n",timer,type,explode_timer);
}
void Missile::load_attack(FILE* file){
	fscanf(file,"%d %d %d\n",&timer,&type,&explode_timer);
}
void Missile::collide_action(RigidBody* b){

}
void  Missile::explode(){
	//std::cout<<"Missile::explode()"<<std::endl;
	for(unsigned i=0;i<collied_units.size();i++){
		if(target==collied_units.at(i)){
			damage_target(damage);
		}else{
			collied_units.at(i)->hp_alter(-damage);
		}
	}
	Audio::AudioController::get_cur_object()->
			play_by_dis("default_sound_effect/Bomb.wav",pos,100);

	explode_timer++;
	//die=true;
}
Display::DrawObject *Missile::get_missile_drawobj(){
	return Display::AllDrawObjects::get_cur_object()->get("attack/ball_missile_1");
}
void Missile::draw_attack(){
	if(explode_timer){
		Display::PointLight *light=new Display::PointLight(
				glm::vec3(pos.x,pos.y,pos.z),
				glm::vec3(fabs(4.0-explode_timer)*8.0,1.0,1.0),false);
		Display::Draw::get_cur_object()->lightControl->push_temp_light(light);
	}else{
		Display::DrawObject *missile_Drawobj=get_missile_drawobj();
		math::Position *dp_pos=new math::Position();
		dp_pos->set_pos(glm::vec3(pos.x,pos.y,pos.z));
		dp_pos->set_scale(glm::vec3(2*radius,2*radius,2*radius));
		dp_pos->set_r(glm::vec3((180.0/M_PI)*atan2(sqrt(vel.x*vel.x+vel.z*vel.z),vel.y),
				(180.0/M_PI)*atan2(vel.x,vel.z),0));
		missile_Drawobj->push_temp_drawdata(new Display::DrawDataObj(dp_pos,true,true));
	}
}
void Missile::attack_update(){
	//std::cout<<"Missile::attack_update()"<<std::endl;
	if(explode_timer){
		explode_timer++;
		if(explode_timer>3)die=true;
		return;
	}
	timer++;
	if(be_collided==true||collided==true){
		explode();
	}
	/*
	if(timer<50){
		this->collision_off=true;
	}else{
		this->collision_off=false;
	}
	*/
	if(target){
		vel*=0.8;
		math::vec3<double> target_pos=target->get_mid_pos();
		math::vec3<double> del_pos=target_pos-pos;
		if(timer<25||(timer<50&&del_pos.y>-3.0)){
			vel.y+=0.045;
		}else{
			timer=50;
			math::vec3<double> del_pos_xz=del_pos;
			del_pos_xz.y=0;
			if(del_pos_xz.get_length()>=1.0){
				del_pos.y/=del_pos_xz.get_length();
			}
			vel+=0.055*del_pos.normalize();
		}
	}else{
		//explode();
	}
}
} /* namespace AOC */
