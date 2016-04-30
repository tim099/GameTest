#ifndef SOURCE_CLASS_GAME_MAP_CUBE_BASIC_ATTACHCUBE_H_
#define SOURCE_CLASS_GAME_MAP_CUBE_BASIC_ATTACHCUBE_H_

#include "class/game/ageOfCube/map/cube/CubeEX.h"

/*
 * this is a child cube type belongs to a larger cube subset
 * (EX: a small piece of cube in a large building occupied several cubes size
 */
namespace AOC{
class AttachCube: public AOC::CubeEX {
public:
	AttachCube();
	virtual ~AttachCube();
};
}
#endif /* SOURCE_CLASS_GAME_MAP_CUBE_BASIC_ATTACHCUBE_H_ */