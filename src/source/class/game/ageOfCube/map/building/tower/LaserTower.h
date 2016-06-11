#ifndef SOURCE_CLASS_GAME_AGEOFCUBE_MAP_BUILDING_TOWER_LASERTOWER_H_
#define SOURCE_CLASS_GAME_AGEOFCUBE_MAP_BUILDING_TOWER_LASERTOWER_H_

#include "class/game/ageOfCube/map/building/Building.h"

namespace AOC {

class LaserTower: public Building{
public:
	LaserTower();
	LaserTower(LaserTower* tower);
	virtual ~LaserTower();
	virtual void building_pre_init();
	virtual AOC::Building* clone(){
		return new LaserTower(this);
	}
	virtual std::string get_name()const{
		return "LaserTower";
	}
};

} /* namespace AOC */

#endif /* SOURCE_CLASS_GAME_AGEOFCUBE_MAP_BUILDING_TOWER_LASERTOWER_H_ */
