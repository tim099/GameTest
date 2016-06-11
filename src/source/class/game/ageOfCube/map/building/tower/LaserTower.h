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
	virtual math::vec3<int> get_cube_large_size(){
		return math::vec3<int>(ceil(size/3.0),ceil(size),ceil(size/3.0));
	}
	virtual AOC::Building* clone(){
		return new LaserTower(this);
	}
	virtual std::string get_name()const{
		return "LaserTower";
	}
	virtual void get_build_on_type(std::vector<int> &v){
		v.push_back(Cube::stone);
	}
protected:
	virtual double get_attack_range(){return 8.0;}
	virtual std::string get_attack_type(){return std::string("Laser");}
	virtual double get_attack_size(){return 0.1*size;}

	virtual void building_update();
	virtual void save_building(FILE * file);
	virtual void load_building(FILE * file);
	virtual void draw_building();
};

} /* namespace AOC */

#endif /* SOURCE_CLASS_GAME_AGEOFCUBE_MAP_BUILDING_TOWER_LASERTOWER_H_ */
