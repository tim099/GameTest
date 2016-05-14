/*
 * BuildingCreater.cpp
 *
 *  Created on: 2016¦~5¤ë14¤é
 *      Author: LukeWu
 */

#include "class/game/ageOfCube/map/building/BuildingCreater.h"
#include "class/game/ageOfCube/map/building/tower/Tower.h"
#include <iostream>


namespace AOC{
BuildingCreater::BuildingCreater() {
	//std::cout<<"LandscapeCreator::LandscapeCreator()"<<std::endl;
	push(new AOC::Tower());
	register_cur();
}
BuildingCreater::~BuildingCreater() {
	//delete handle by Tim::MapContainer
}
void BuildingCreater::push(AOC::Building* obj){
	obj->building_pre_init();
	creator.push(obj->get_name(),obj);
}
AOC::Building* BuildingCreater::create(std::string type_name){
	if (!creator.get(type_name)) {
		std::cerr << "LandScape name:" << type_name
				<< " not exist in this LandScapeCreator" << std::endl;
		return 0;
	}
	return creator.get(type_name)->create_building();
}
}
