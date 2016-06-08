#ifndef SOURCE_CLASS_GAME_MAP_CUBE_BASIC_ATTACHCUBE_H_
#define SOURCE_CLASS_GAME_MAP_CUBE_BASIC_ATTACHCUBE_H_

#include "class/game/ageOfCube/map/cube/CubeEX.h"

/*
 * this is a child cube belongs to CubeLarge
 * (EX: a small piece of cube in a large building occupied several cubes size
 */
namespace AOC{
class CubeLarge;
class AttachCube: public CubeEX {
public:
	AttachCube(int x,int y,int z,CubeLarge *parent);
	virtual ~AttachCube();
	virtual void remove_cubeEX();
	inline CubeLarge* get_parent(){
		return parent;
	}
	virtual AttachCube* get_attachCube(){
		return this;
	}
	virtual CubeEX* get_real_cube();
	int x;
	int y;
	int z;
	bool removing;
	CubeLarge *parent;
};
}
#endif /* SOURCE_CLASS_GAME_MAP_CUBE_BASIC_ATTACHCUBE_H_ */
