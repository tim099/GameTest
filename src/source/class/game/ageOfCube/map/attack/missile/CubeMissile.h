#ifndef SOURCE_CLASS_GAME_AGEOFCUBE_MAP_ATTACK_MISSILE_CUBEMISSILE_H_
#define SOURCE_CLASS_GAME_AGEOFCUBE_MAP_ATTACK_MISSILE_CUBEMISSILE_H_

#include "class/game/ageOfCube/map/attack/missile/Missile.h"

namespace AOC {

class CubeMissile: public Missile {
public:
	CubeMissile();
	CubeMissile(CubeMissile* cube);
	virtual ~CubeMissile();
	virtual Attack* clone(){
		return new CubeMissile(this);
	}
	virtual std::string get_name(){
		return std::string("CubeMissile");
	}
protected:
	virtual Display::DrawObject *get_missile_drawobj();
};

} /* namespace AOC */

#endif /* SOURCE_CLASS_GAME_AGEOFCUBE_MAP_ATTACK_MISSILE_CUBEMISSILE_H_ */
