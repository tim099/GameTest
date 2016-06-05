#ifndef SOURCE_CLASS_GAME_MAP_CUBE_BASIC_DIRT_H_
#define SOURCE_CLASS_GAME_MAP_CUBE_BASIC_DIRT_H_

#include "class/game/ageOfCube/map/cube/basic/BasicCube.h"
namespace AOC{
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
	virtual bool jumpable(){
		return true;
	}
	virtual void collide(physic::RigidBody *b);
};
}
#endif /* SOURCE_CLASS_GAME_MAP_CUBE_BASIC_DIRT_H_ */
