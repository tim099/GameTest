#ifndef SOURCE_CLASS_GAME_MAP_CUBE_BASIC_DIRT_H_
#define SOURCE_CLASS_GAME_MAP_CUBE_BASIC_DIRT_H_

#include "class/game/map/cube/basic/BasicCube.h"

class Dirt: public BasicCube {
public:
	Dirt();
	virtual ~Dirt();
	virtual std::string get_name()const{
		return "Dirt";
	}
	virtual unsigned char get_type(){
		return Cube::dirt;
	}
};

#endif /* SOURCE_CLASS_GAME_MAP_CUBE_BASIC_DIRT_H_ */
