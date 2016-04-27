#ifndef SOURCE_CLASS_GAME_MAP_CUBE_BASIC_SAND_SAND_H_
#define SOURCE_CLASS_GAME_MAP_CUBE_BASIC_SAND_SAND_H_

#include "class/game/ageOfCube/map/cube/basic/BasicCube.h"
namespace AOC{
class Sand: public BasicCube {
public:
	Sand();
	virtual ~Sand();
	virtual std::string get_name()const{
		return "Sand";
	}
	virtual unsigned char get_type(){
		return Cube::sand;
	}
};
}
#endif /* SOURCE_CLASS_GAME_MAP_CUBE_BASIC_SAND_SAND_H_ */
