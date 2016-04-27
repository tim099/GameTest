#include "class/game/ageOfCube/map/landscape/LandscapeCreator.h"
#include "class/game/ageOfCube/map/landscape/tree/Tree.h"
#include <iostream>
namespace AOC{
LandscapeCreator::LandscapeCreator() {
	//std::cout<<"LandscapeCreator::LandscapeCreator()"<<std::endl;
	push(new AOC::Tree());
	register_cur();
}
LandscapeCreator::~LandscapeCreator() {
	//delete handle by Tim::MapContainer
}
void LandscapeCreator::push(AOC::Landscape* obj){
	obj->landscape_pre_init();
	creator.push(obj->get_name(),obj);
}
AOC::Landscape* LandscapeCreator::create(std::string type_name){
	if (!creator.get(type_name)) {
		std::cerr << "LandScape name:" << type_name
				<< " not exist in this LandScapeCreator" << std::endl;
		return 0;
	}
	return creator.get(type_name)->create_landscape();
}
}
