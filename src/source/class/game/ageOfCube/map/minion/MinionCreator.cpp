#include "class/game/ageOfCube/map/minion/MinionCreator.h"
#include "class/game/ageOfCube/map/minion/ball/Ball.h"

namespace AOC {

MinionCreator::MinionCreator() {
	push(new Ball());
	register_cur();
}
MinionCreator::~MinionCreator() {

}
void MinionCreator::push(AOC::Minion* obj){
	obj->minion_pre_init();
	creator.push(obj->get_name(),obj);
}
AOC::Minion* MinionCreator::create(std::string type_name){
	if (!creator.get(type_name)) {
		std::cerr << "Minion name:" << type_name
				<< " not exist in this MinionCreatorCreator" << std::endl;
		return 0;
	}
	return creator.get(type_name)->clone();
}
} /* namespace AOC */
