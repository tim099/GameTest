#ifndef SOURCE_CLASS_GAME_AGEOFCUBE_MAP_ATTACK_LASER_LASER_H_
#define SOURCE_CLASS_GAME_AGEOFCUBE_MAP_ATTACK_LASER_LASER_H_

#include "class/game/ageOfCube/map/attack/Attack.h"

namespace AOC {

class Laser: public Attack {
public:
	virtual void attack_pre_init();
	Laser();
	Laser(Laser* laser);
	virtual ~Laser();

	virtual Attack* clone(){
		return new Laser(this);
	}
	virtual std::string get_name(){
		return std::string("Laser");
	}
	virtual void save_attack(FILE* file);
	virtual void load_attack(FILE* file);
	virtual void draw_attack();
	virtual void attack_update();
protected:
	void burn_target();
	int timer,burn_time;
	bool burning_target;
};

} /* namespace AOC */

#endif /* SOURCE_CLASS_GAME_AGEOFCUBE_MAP_ATTACK_LASER_LASER_H_ */
