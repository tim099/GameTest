#include "class/game/ageOfCube/map/minion/Minion.h"
#include "class/game/ageOfCube/unit/UnitController.h"
#include "class/game/ageOfCube/map/Map.h"
#include "class/game/ageOfCube/map/DisplayMap.h"
#include <iostream>
namespace AOC {

Minion::Minion() {
	minion_created=false;
}
Minion::~Minion() {
	/*
	if(minion_created){
		UnitController::get_cur_object()->remove_minion(this);
	}
	*/
}
void Minion::save(FILE * file){
	save_unit(file);
	rigid_body.save(file);
	save_minion(file);
}
void Minion::load(FILE * file){
	load_unit(file);
	rigid_body.load(file);
	load_minion(file);
}
void Minion::recruit(){
	//push_minion_to_controller();
	minion_created=true;
	push_to_controller();
}
void Minion::draw(){
	math::vec3<double> s=Map::get_cur_object()->dp_map->dp_start;
	math::vec3<double> e=Map::get_cur_object()->dp_map->dp_end;
	math::vec3<double> pos=get_position();
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
void Minion::unit_update(){
	//std::cout<<"unit_update()"<<std::endl;
	rigid_body.set_detect_collision();
	minion_update();
}
} /* namespace AOC */
