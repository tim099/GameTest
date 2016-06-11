#include "class/game/ageOfCube/map/attack/AttackCreator.h"
#include "class/game/ageOfCube/map/attack/missile/Missile.h"
#include "class/game/ageOfCube/map/attack/missile/CubeMissile.h"
#include "class/game/ageOfCube/map/attack/laser/Laser.h"
namespace AOC {

AttackCreator::AttackCreator() {
	push(new Missile());
	push(new CubeMissile());

	push(new Laser());
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
