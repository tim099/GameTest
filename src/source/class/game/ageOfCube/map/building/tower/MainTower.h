#ifndef SOURCE_CLASS_GAME_AGEOFCUBE_MAP_BUILDING_TOWER_MAINTOWER_H_
#define SOURCE_CLASS_GAME_AGEOFCUBE_MAP_BUILDING_TOWER_MAINTOWER_H_

#include "class/game/ageOfCube/map/building/Building.h"
namespace Display{
class DrawObject;
}
namespace AOC {

class MainTower: public Building {
public:
	MainTower();
	MainTower(MainTower* tower);
	virtual ~MainTower();
	virtual void building_pre_init();
	virtual math::vec3<int> get_cube_large_size(){
		return math::vec3<int>(ceil(size/3.0),ceil(size),ceil(size/3.0));
	}
	virtual AOC::Building* clone(){
		return new MainTower(this);
	}
	virtual std::string get_name()const{
		return "MainTower";
	}

protected:
	virtual void unit_create();
	virtual void killed();

	virtual void building_update();
	virtual void save_building(FILE * file);
	virtual void load_building(FILE * file);
	virtual void draw_building();
	Display::DrawObject *tower_Drawobj;
	int timer,loop_time;
};

} /* namespace AOC */

#endif /* SOURCE_CLASS_GAME_AGEOFCUBE_MAP_BUILDING_TOWER_MAINTOWER_H_ */
