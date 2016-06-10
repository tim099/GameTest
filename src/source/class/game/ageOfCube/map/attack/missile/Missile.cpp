#include "class/game/ageOfCube/map/attack/missile/Missile.h"
#include "class/display/draw/drawObject/AllDrawObjects.h"
#include "class/audio/AudioController.h"
#include "class/game/ageOfCube/map/unit/Unit.h"
#include "class/display/light/LightControl.h"
#include "class/display/draw/Draw.h"
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
	timer=0;
	type=0;
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
		collied_units.at(i)->hp_alter(-damage);
	}
	Audio::AudioController::get_cur_object()->
			play_by_dis("default_sound_effect/Bomb.wav",pos,200);
	Display::PointLight *light=new Display::PointLight(
			glm::vec3(pos.x,pos.y,pos.z),
			glm::vec3(10.0,1.0,1.0),false);

	Display::Draw::get_cur_object()->lightControl->push_temp_light(light);
	die=true;
}
void Missile::draw_attack(){
	Display::DrawObject *missile_Drawobj=Display::AllDrawObjects::get_cur_object()->get("attack/ball_missile_1");
	//Display::DrawObject *missile_Drawobj=Display::AllDrawObjects::get_cur_object()->get("attack/cube_missile_1");
	math::Position *dp_pos=new math::Position();
	dp_pos->set_pos(glm::vec3(pos.x,pos.y,pos.z));
	dp_pos->set_scale(glm::vec3(2*radius,2*radius,2*radius));
	missile_Drawobj->push_temp_drawdata(new Display::DrawDataObj(dp_pos,true,true));
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
