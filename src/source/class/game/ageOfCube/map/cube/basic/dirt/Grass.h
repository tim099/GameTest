#ifndef SOURCE_CLASS_GAME_MAP_CUBE_BASIC_DIRT_GRASS_H_
#define SOURCE_CLASS_GAME_MAP_CUBE_BASIC_DIRT_GRASS_H_

#include "class/game/ageOfCube/map/cube/basic/dirt/Dirt.h"
namespace AOC{
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
	virtual bool jumpable(){
		return true;
	}
	virtual void collide(physic::RigidBody *b);
};
}
#endif /* SOURCE_CLASS_GAME_MAP_CUBE_BASIC_DIRT_GRASS_H_ */
