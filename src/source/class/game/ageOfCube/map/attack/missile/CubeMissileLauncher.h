#ifndef SOURCE_CLASS_GAME_AGEOFCUBE_MAP_ATTACK_MISSILE_CUBEMISSILELAUNCHER_H_
#define SOURCE_CLASS_GAME_AGEOFCUBE_MAP_ATTACK_MISSILE_CUBEMISSILELAUNCHER_H_

#include "class/game/ageOfCube/map/attack/missile/MissileLauncher.h"

namespace AOC {

class CubeMissileLauncher: public MissileLauncher {
public:
	CubeMissileLauncher();
	virtual ~CubeMissileLauncher();
	virtual Weapon* clone(){
		return new CubeMissileLauncher();
	}
	virtual std::string get_name(){
		return "CubeMissileLauncher";
	}
	virtual std::string get_attack_type(){
		return "CubeMissile";
	}
protected:
	virtual void draw_weapon();
};

} /* namespace AOC */

#endif /* SOURCE_CLASS_GAME_AGEOFCUBE_MAP_ATTACK_MISSILE_CUBEMISSILELAUNCHER_H_ */
