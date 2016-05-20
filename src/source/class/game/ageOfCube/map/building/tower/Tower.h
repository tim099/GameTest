/*
 * Tower.h
 *
 *  Created on: 2016�~5��14��
 *      Author: LukeWu
 */

#ifndef SOURCE_CLASS_GAME_AGEOFCUBE_MAP_BUILDING_TOWER_TOWER_H_
#define SOURCE_CLASS_GAME_AGEOFCUBE_MAP_BUILDING_TOWER_TOWER_H_

#include "class/game/ageOfCube/map/building/Building.h"
#include "class/tim/math/Position.h"

namespace Display{
class DrawObject;
}

namespace AOC {

class Tower : public AOC::Building {
	static const unsigned char tower=0;
public:
	Tower();
	Tower(Tower *tower);
	virtual ~Tower();
	virtual void building_pre_init();
	virtual math::vec3<int> get_cube_large_size(){
		return math::vec3<int>(2,6,2);
	}
	virtual AOC::Building* create_building(){
		return new Tower(this);
	}
	virtual std::string get_name()const{
		return "Tower";
	}
	virtual bool draw_cube(){
		return true;
	}
	virtual void set_pos(int x,int y,int z);
	virtual void draw();
	math::Position *pos;
	unsigned char tower_type;
protected:
	virtual void save_building(FILE * file);
	virtual void load_building(FILE * file);
	Display::DrawObject *tower_Drawobj;
};

}

#endif /* SOURCE_CLASS_GAME_AGEOFCUBE_MAP_BUILDING_TOWER_TOWER_H_ */
