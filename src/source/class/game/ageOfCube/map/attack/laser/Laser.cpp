#include "class/game/ageOfCube/map/attack/laser/Laser.h"
#include "class/display/draw/drawObject/AllDrawObjects.h"
#include "class/audio/AudioController.h"
#include "class/game/ageOfCube/map/unit/Unit.h"
#include "class/display/light/LightControl.h"
#include "class/display/draw/Draw.h"
namespace AOC {
void Laser::attack_pre_init(){

}
Laser::Laser() {
	collision_off=true;
	timer=0;
	burn_time=10;
	burning_target=false;
}
Laser::Laser(Laser* laser) {
	collision_off=true;
	timer=0;
	burn_time=10;
	burning_target=false;
}
Laser::~Laser() {

}
void Laser::save_attack(FILE* file){
	fprintf(file,"%d %d\n",timer,burn_time);
}
void Laser::load_attack(FILE* file){
	fscanf(file,"%d %d\n",&timer,&burn_time);
}
void Laser::draw_attack(){
	if(!target)return;
	Display::DrawObject *drawobj=Display::AllDrawObjects::get_cur_object()->get("attack/laser");
	math::Position *dp_pos=new math::Position();
	math::vec3<double> del_pos=target->get_mid_pos()-pos;
	math::vec3<double> pos_mid=0.5*(target->get_mid_pos()+pos);

	dp_pos->set_pos(glm::vec3(pos_mid.x,pos_mid.y,pos_mid.z));
	dp_pos->set_scale(glm::vec3(0.05,del_pos.get_length(),0.05));

	dp_pos->set_r(glm::vec3((180.0/M_PI)*atan2(sqrt(del_pos.x*del_pos.x+del_pos.z*del_pos.z),del_pos.y),
			(180.0/M_PI)*atan2(del_pos.x,del_pos.z),0));

	drawobj->push_temp_drawdata(new Display::DrawDataObj(dp_pos,false,true));
	if(burning_target){
		math::vec3<double> target_pos=target->get_mid_pos();
		Display::PointLight *light=new Display::PointLight(
				glm::vec3(target_pos.x,target_pos.y,target_pos.z),
				glm::vec3(10.0,10.0,10.0),false);
		Display::Draw::get_cur_object()->lightControl->push_temp_light(light);

		light=new Display::PointLight(
				glm::vec3(pos.x,pos.y,pos.z),
				glm::vec3(50.0,50.0,50.0),false);
		Display::Draw::get_cur_object()->lightControl->push_temp_light(light);
	}
}
void Laser::burn_target(){
	burning_target=false;
	if(!target)return;
	burning_target=true;
	damage_target(damage);
	//target->hp_alter(-damage);
	//if(target->get_is_dead()){
		//pos=target->get_mid_pos();
		//pos.y+=5.0;
	//}
}
void Laser::attack_update(){
	timer++;
	burn_target();
	if(timer==1){
		Audio::AudioController::get_cur_object()->
				play_by_dis("default_sound_effect/laser.wav",pos,100);
	}
	if(timer>burn_time){
		die=true;
	}
}
} /* namespace AOC */
