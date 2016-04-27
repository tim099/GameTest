#ifndef SOURCE_CLASS_GAME_MAP_CUBE_BASIC_STONE_STONE_H_
#define SOURCE_CLASS_GAME_MAP_CUBE_BASIC_STONE_STONE_H_

#include "class/game/ageOfCube/map/cube/basic/BasicCube.h"
namespace AOC{
class Stone: public BasicCube {
public:
	Stone();
	virtual ~Stone();
	virtual std::string get_name()const{
		return "Stone";
	}
	virtual unsigned char get_type(){
		return Cube::stone;
	}
};
}
#endif /* SOURCE_CLASS_GAME_MAP_CUBE_BASIC_STONE_STONE_H_ */
