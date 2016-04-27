#ifndef SOURCE_CLASS_GAME_MAP_CUBE_BASIC_STONE_COAL_H_
#define SOURCE_CLASS_GAME_MAP_CUBE_BASIC_STONE_COAL_H_

#include "class/game/ageOfCube/map/cube/basic/stone/Stone.h"
namespace AOC{
class Coal: public Stone {
public:
	Coal();
	virtual ~Coal();
	virtual std::string get_name()const{
		return "Coal";
	}
	virtual unsigned char get_type(){
		return Cube::coal;
	}
};
}
#endif /* SOURCE_CLASS_GAME_MAP_CUBE_BASIC_STONE_COAL_H_ */
