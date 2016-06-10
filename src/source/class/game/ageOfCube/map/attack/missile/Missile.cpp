#include "class/game/ageOfCube/map/attack/missile/Missile.h"
#include "class/display/draw/drawObject/AllDrawObjects.h"
#include "class/audio/AudioController.h"
#include "class/game/ageOfCube/map/unit/Unit.h"
namespace AOC {
void Missile::attack_pre_init(){
	missile_Drawobj=Display::AllDrawObjects::get_cur_object()->get("minion/ball");
}
Missile::Missile() {
	missile_Drawobj=0;
	radius=0.1;
	timer=0;
}
Missile::Missile(Missile* missile){
	missile_Drawobj=missile->missile_Drawobj;
	radius=missile->radius;
	timer=0;
}
Missile::~Missile() {

}
void Missile::save_attack(FILE* file){
	fprintf(file,"%d\n",timer);
}
void Missile::load_attack(FILE* file){
	fscanf(file,"%d\n",&timer);
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
		vel*=0.9;
		if(timer<50){
			vel.y+=0.025;
		}else{
			math::vec3<double> target_pos=target->get_mid_pos();
			math::vec3<double> del_pos=target_pos-pos;
			vel+=0.025*del_pos.normalize();
			if(del_pos.get_length()<0.1)explode();
		}
	}else{
		//explode();
	}
}
} /* namespace AOC */
