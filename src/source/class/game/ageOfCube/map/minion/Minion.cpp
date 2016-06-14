#include "class/game/ageOfCube/map/minion/Minion.h"
#include "class/game/ageOfCube/map/unit/UnitController.h"
#include "class/game/ageOfCube/map/Map.h"
#include "class/game/ageOfCube/map/DisplayMap.h"
#include "class/game/ageOfCube/map/unit/UnitController.h"
#include "class/display/draw/drawObject/AllDrawObjects.h"
#include <iostream>
namespace AOC {

Minion::Minion() {
	//std::cout<<"Minion::Minion()="<<this<<std::endl;
	minion_created=false;
}
Minion::~Minion() {
	//std::cout<<"Minion::~Minion()="<<this<<std::endl;
}
void Minion::save(FILE * file){
	save_unit(file);
	rigid_body.save_rigid_body(file);
	save_minion(file);
}
void Minion::load(FILE * file){
	load_unit(file);
	rigid_body.load_rigid_body(file);
	load_minion(file);
}
double Minion::get_attack_size(){
	return rigid_body.radius;
}
void Minion::create_minion(){
	minion_created=true;
	create_unit();

	push_component(&rigid_body);
}
math::vec3<int> Minion::get_pos_int(){
	return math::vec3<int>(
			get_pos().x/Map::CUBE_SIZE,
			get_pos().y/Map::CUBE_SIZE,
			get_pos().z/Map::CUBE_SIZE);
}
void Minion::draw_hp(){
	if(get_hp()==get_max_hp())return;
	Display::AllDrawObjects* all_dobj=Display::AllDrawObjects::get_cur_object();
	double hp_percent=((double)get_hp()/(double)get_max_hp());
	//std::cout<<"hp_percent="<<hp_percent<<std::endl;
	math::Position* pos;
	Display::DrawDataObj* data;
	if(get_hp()>0){
		pos=new math::Position();
		pos->set_pos(glm::vec3(
				get_pos().x,
				get_pos().y+1.5*rigid_body.radius,
				get_pos().z+(1.0-hp_percent)*rigid_body.radius));
		pos->set_scale(glm::vec3(
				0.3*rigid_body.radius,
				0.3*rigid_body.radius,
				2*hp_percent*rigid_body.radius));
		data=new Display::DrawDataObj(pos,true,true);
		all_dobj->get("misc/hp_light")->push_temp_drawdata(data);
	}
	if(get_hp()<get_max_hp()){
		pos=new math::Position();
		pos->set_pos(glm::vec3(
				get_pos().x,
				get_pos().y+1.5*rigid_body.radius,
				get_pos().z-hp_percent*rigid_body.radius));
		pos->set_scale(glm::vec3(
				0.3*rigid_body.radius,
				0.3*rigid_body.radius,
				2*(1.0-hp_percent)*rigid_body.radius));
		data=new Display::DrawDataObj(pos,true,true);
		all_dobj->get("misc/hp_dark")->push_temp_drawdata(data);
	}


}
void Minion::draw(){
	if(is_dead){
		return;
	}
	math::vec3<double> s=Map::get_cur_object()->dp_map->dp_start;
	math::vec3<double> e=Map::get_cur_object()->dp_map->dp_end;
	math::vec3<double> pos=get_pos();
	if(pos>=s&&pos<=e){
		draw_hp();
		draw_minion();
	}else{
		//draw_minion();
		//std::cout<<"Minion::draw() not display"<<std::endl;
	}

}
/*
void Minion::push_minion_to_controller(){
	if(minion_created)return;
	//UnitController::get_cur_object()->push_minion(this);
	minion_created=true;
}
*/
void Minion::move_to(math::vec3<double> target,double vel){
	math::vec3<double>pos_del=target-get_pos();
	math::vec3<double>pos_del_xz=pos_del;
	pos_del_xz.y=0;
	rigid_body.vel*=0.85;
	rigid_body.vel+=vel*pos_del_xz.normalize();
	rigid_body.vel.y+=0.016*pos_del.normalize().y;
}
void Minion::unit_update(){
	//std::cout<<"unit_update()"<<std::endl;
	rigid_body.set_detect_collision();
	minion_update();
}
} /* namespace AOC */
