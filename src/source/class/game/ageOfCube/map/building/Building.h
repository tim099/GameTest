#ifndef SOURCE_CLASS_GAME_MAP_BUILDING_BUILDING_H_
#define SOURCE_CLASS_GAME_MAP_BUILDING_BUILDING_H_

#include "class/game/ageOfCube/map/cube/CubeLarge.h"
#include "class/game/ageOfCube/unit/Unit.h"
namespace AOC {
class Map;
class Building: public CubeLarge ,
				public Unit
{
public:
	Building();
	virtual ~Building();
	virtual void building_pre_init();
	virtual AOC::Building* get_building(){
		return this;
	}
	virtual AOC::Building* create_building(){
		return 0;
	}
	virtual std::string get_name()const{
		return "Building";
	}
	void draw_buildable(Map *map,int x,int y,int z);
	virtual void unit_update();
protected:
	virtual void building_update(){

	}

	virtual void save_cubeEX(FILE * file);
	virtual void load_cubeEX(FILE * file);
	virtual void save_building(FILE * file);
	virtual void load_building(FILE * file);
	float size;
};
}

#endif /* SOURCE_CLASS_GAME_MAP_BUILDING_BUILDING_H_ */
