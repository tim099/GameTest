#ifndef SOURCE_CLASS_GAME_AGEOFCUBE_MAP_ATTACK_LASER_LASERCANNON_H_
#define SOURCE_CLASS_GAME_AGEOFCUBE_MAP_ATTACK_LASER_LASERCANNON_H_

#include "class/game/ageOfCube/map/attack/weapon/Weapon.h"

namespace AOC {

class LaserCannon: public Weapon {
public:
	LaserCannon();
	virtual ~LaserCannon();
	virtual Weapon* clone(){
		return new LaserCannon();
	}
	virtual std::string get_name(){
		return "LaserCannon";
	}
	virtual std::string get_attack_type(){
		return "Laser";
	}
};

} /* namespace AOC */

#endif /* SOURCE_CLASS_GAME_AGEOFCUBE_MAP_ATTACK_LASER_LASERCANNON_H_ */
