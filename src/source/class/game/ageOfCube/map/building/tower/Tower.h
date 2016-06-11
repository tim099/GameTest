#ifndef SOURCE_CLASS_GAME_AGEOFCUBE_MAP_BUILDING_TOWER_TOWER_H_
#define SOURCE_CLASS_GAME_AGEOFCUBE_MAP_BUILDING_TOWER_TOWER_H_

#include "class/game/ageOfCube/map/building/Building.h"
#include <cmath>
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
		return math::vec3<int>(ceil(size/3.0),ceil(size),ceil(size/3.0));
	}
	virtual AOC::Building* clone(){
		return new Tower(this);
	}
	virtual std::string get_name()const{
		return "Tower";
	}
	virtual void get_build_on_type(std::vector<int> &v);


	unsigned char tower_type;
protected:
	virtual double get_attack_range(){return 15.0;}
	virtual std::string get_attack_type(){return std::string("CubeMissile");}
	virtual double get_attack_size(){return 0.12*size;}

	virtual void building_set_pos(int x,int y,int z);
	virtual void building_update();
	virtual void save_building(FILE * file);
	virtual void load_building(FILE * file);
	virtual void draw_building();

	Display::DrawObject *tower_Drawobj;
	int timer;
};

}

#endif /* SOURCE_CLASS_GAME_AGEOFCUBE_MAP_BUILDING_TOWER_TOWER_H_ */
