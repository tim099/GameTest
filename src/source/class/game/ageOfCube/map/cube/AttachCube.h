#ifndef SOURCE_CLASS_GAME_MAP_CUBE_BASIC_ATTACHCUBE_H_
#define SOURCE_CLASS_GAME_MAP_CUBE_BASIC_ATTACHCUBE_H_

#include "class/game/ageOfCube/map/cube/CubeEX.h"

/*
 * this is a child cube belongs to CubeLarge
 * (EX: a small piece of cube in a large building occupied several cubes size
 */
namespace AOC{
class AttachCube: public CubeEX {
public:
	AttachCube(int x,int y,int z);
	virtual ~AttachCube();

	int x;
	int y;
	int z;
};
}
#endif /* SOURCE_CLASS_GAME_MAP_CUBE_BASIC_ATTACHCUBE_H_ */
