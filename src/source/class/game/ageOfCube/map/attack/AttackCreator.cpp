#include "class/game/ageOfCube/map/attack/AttackCreator.h"

namespace AOC {

AttackCreator::AttackCreator() {
	register_cur();
}
AttackCreator::~AttackCreator() {

}
void AttackCreator::push(Attack* obj){
	obj->attack_pre_init();
	creator.push(obj->get_name(),obj);
}
Attack* AttackCreator::create(std::string type_name){
	if (!creator.get(type_name)) {
		std::cerr << "Attack name:" << type_name
				<< " not exist in this AttackCreator" << std::endl;
		return 0;
	}
	return creator.get(type_name)->clone();
}
} /* namespace AOC */
