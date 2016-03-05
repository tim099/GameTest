#include "class/game/map/landscape/LandscapeCreator.h"
#include "class/game/map/landscape/tree/Tree.h"
LandscapeCreator::LandscapeCreator() {
	push(new Tree());
}
LandscapeCreator::~LandscapeCreator() {
	//delete handle by Tim::MapContainer
}
void LandscapeCreator::push(Landscape* obj){
	obj->landscape_pre_init();
	creator.push(obj->get_name(),obj);
}
Landscape* LandscapeCreator::create(std::string type_name){
	if (!creator.get(type_name)) {
		std::cerr << "LandScape name:" << type_name
				<< " not exist in this LandScapeCreator" << std::endl;
		return 0;
	}
	return creator.get(type_name)->create_landscape();
}
