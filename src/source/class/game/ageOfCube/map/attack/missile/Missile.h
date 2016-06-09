#ifndef SOURCE_CLASS_GAME_AGEOFCUBE_MAP_ATTACK_MISSILE_MISSILE_H_
#define SOURCE_CLASS_GAME_AGEOFCUBE_MAP_ATTACK_MISSILE_MISSILE_H_

#include "class/game/ageOfCube/map/attack/Attack.h"

namespace AOC {

class Missile: public Attack {
public:
	virtual void attack_pre_init();
	Missile();
	Missile(Missile* missile);
	virtual ~Missile();
	virtual Attack* clone(){
		return new Missile(this);
	}
	virtual std::string get_name(){
		return std::string("Missile");
	}
protected:
	virtual void draw_attack();
	virtual void attack_update();
	Display::DrawObject *missile_Drawobj;
};

} /* namespace AOC */

#endif /* SOURCE_CLASS_GAME_AGEOFCUBE_MAP_ATTACK_MISSILE_MISSILE_H_ */
