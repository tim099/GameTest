#include "class/game/ageOfCube/map/attack/weapon/WeaponCreator.h"
#include "class/game/ageOfCube/map/attack/missile/MissileLauncher.h"
#include "class/game/ageOfCube/map/attack/missile/CubeMissileLauncher.h"
#include "class/game/ageOfCube/map/attack/laser/LaserCannon.h"
namespace AOC {

WeaponCreator::WeaponCreator() {
	push(new MissileLauncher());
	push(new CubeMissileLauncher());
	push(new LaserCannon());

	register_cur();
}
WeaponCreator::~WeaponCreator() {

}
Weapon* WeaponCreator::create(std::string type_name){
	if (!creator.get(type_name)) {
		std::cerr << "Weapon name:" << type_name
				<< " not exist in this WeaponCreator" << std::endl;
		return 0;
	}
	return creator.get(type_name)->clone();
}
void WeaponCreator::push(Weapon* obj){
	obj->weapon_pre_init();
	creator.push(obj->get_name(),obj);
}
} /* namespace AOC */
