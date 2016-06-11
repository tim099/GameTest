#include "class/game/ageOfCube/map/building/BuildingCreator.h"
#include "class/game/ageOfCube/map/building/tower/Tower.h"
#include "class/game/ageOfCube/map/building/tower/BallSpawnTower.h"
#include "class/game/ageOfCube/map/building/tower/MainTower.h"
#include "class/game/ageOfCube/map/building/tower/LaserTower.h"
#include <iostream>


namespace AOC{
BuildingCreator::BuildingCreator() {
	//std::cout<<"BuildingCreator::BuildingCreator()"<<std::endl;
	push(new AOC::Tower());
	push(new AOC::BallSpawnTower());
	push(new AOC::MainTower());
	push(new AOC::LaserTower());
	register_cur();
}
BuildingCreator::~BuildingCreator() {
	//delete handle by Tim::MapContainer
}
void BuildingCreator::push(AOC::Building* obj){
	obj->building_pre_init();
	creator.push(obj->get_name(),obj);
}
AOC::Building* BuildingCreator::create(std::string type_name){
	if (!creator.get(type_name)) {
		std::cerr << "Building name:" << type_name
				<< " not exist in this BuildingCreator" << std::endl;
		return 0;
	}
	return creator.get(type_name)->clone();
}
}
