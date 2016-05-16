#ifndef SOURCE_CLASS_GAME_MAP_BUILDING_BUILDING_H_
#define SOURCE_CLASS_GAME_MAP_BUILDING_BUILDING_H_

#include "class/game/ageOfCube/map/cube/CubeEX.h"

namespace AOC {

class Building: public CubeEX  {
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
protected:
	virtual void save_cubeEX(FILE * file);
	virtual void load_cubeEX(FILE * file);
	virtual void save_building(FILE * file);
	virtual void load_building(FILE * file);
};
}

#endif /* SOURCE_CLASS_GAME_MAP_BUILDING_BUILDING_H_ */
