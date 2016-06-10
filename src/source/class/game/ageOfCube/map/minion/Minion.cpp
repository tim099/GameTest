#include "class/game/ageOfCube/map/minion/Minion.h"
#include "class/game/ageOfCube/map/unit/UnitController.h"
#include "class/game/ageOfCube/map/Map.h"
#include "class/game/ageOfCube/map/DisplayMap.h"
#include "class/game/ageOfCube/map/unit/UnitController.h"
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
	return 0.5*rigid_body.radius;
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
void Minion::draw(){
	math::vec3<double> s=Map::get_cur_object()->dp_map->dp_start;
	math::vec3<double> e=Map::get_cur_object()->dp_map->dp_end;
	math::vec3<double> pos=get_pos();
	if(pos>=s&&pos<=e){
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
	//set_vel(vel*pos_del.normalize());
	rigid_body.vel*=0.6;
	rigid_body.vel+=vel*pos_del.normalize();
}
void Minion::unit_update(){
	//std::cout<<"unit_update()"<<std::endl;
	rigid_body.set_detect_collision();
	minion_update();
}
} /* namespace AOC */
