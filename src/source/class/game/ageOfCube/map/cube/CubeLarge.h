#ifndef SOURCE_CLASS_GAME_AGEOFCUBE_MAP_CUBE_CUBELARGE_H_
#define SOURCE_CLASS_GAME_AGEOFCUBE_MAP_CUBE_CUBELARGE_H_

#include "class/game/ageOfCube/map/cube/CubeEX.h"
#include "class/game/ageOfCube/map/cube/AttachCube.h"
#include "class/tim/math/vec3.h"
#include <vector>
namespace AOC {
class Map;
class CubeLarge: public CubeEX {
public:
	CubeLarge();
	virtual ~CubeLarge();

	//return the cube that CubeLarge take place,except the original place(0,0,0)
	virtual void get_attach_cube(std::vector<AttachCube*> &attach_cubes){
		//attach_cubes.push_back(new AttachCube(0,0,0));
	}
	//the ground that should build on
	virtual void get_build_on(std::vector<math::vec3<int> > &build_on){
		build_on.push_back(math::vec3<int>(0,-1,0));
	}
	virtual bool build(Map *map,int x,int y,int z);
	std::vector<AttachCube*> attach_cubes;
	int x,y,z;
};

} /* namespace AOC */

#endif /* SOURCE_CLASS_GAME_AGEOFCUBE_MAP_CUBE_CUBELARGE_H_ */
