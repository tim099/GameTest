#ifndef SOURCE_CLASS_GAME_MAP_CUBE_BASIC_DIRT_GRASS_H_
#define SOURCE_CLASS_GAME_MAP_CUBE_BASIC_DIRT_GRASS_H_

#include "class/game/map/cube/basic/dirt/Dirt.h"

class Grass: public Dirt {
public:
	Grass();
	virtual ~Grass();
	virtual std::string get_name()const{
		return "Grass";
	}
	virtual unsigned char get_type(){
		return Cube::grass;
	}
};

#endif /* SOURCE_CLASS_GAME_MAP_CUBE_BASIC_DIRT_GRASS_H_ */
