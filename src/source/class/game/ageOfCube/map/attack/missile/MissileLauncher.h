#ifndef SOURCE_CLASS_GAME_AGEOFCUBE_MAP_ATTACK_MISSILE_MISSILELAUNCHER_H_
#define SOURCE_CLASS_GAME_AGEOFCUBE_MAP_ATTACK_MISSILE_MISSILELAUNCHER_H_

#include "class/game/ageOfCube/map/attack/weapon/Weapon.h"

namespace AOC {

class MissileLauncher: public Weapon {
public:
	MissileLauncher();
	virtual ~MissileLauncher();
	virtual Weapon* clone(){
		return new MissileLauncher();
	}
	virtual std::string get_name(){
		return "MissileLauncher";
	}
	virtual std::string get_attack_type(){
		return "Missile";
	}
protected:
	virtual void weapon_update();
	virtual void draw_weapon();
};

} /* namespace AOC */

#endif /* SOURCE_CLASS_GAME_AGEOFCUBE_MAP_ATTACK_MISSILE_MISSILELAUNCHER_H_ */
