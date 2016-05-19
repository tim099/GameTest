#include "class/game/ageOfCube/map/cube/CubeLarge.h"
#include "class/game/ageOfCube/map/Map.h"
namespace AOC {

CubeLarge::CubeLarge() {
	x=0,y=0,z=0;
}
CubeLarge::~CubeLarge() {
	Map *map=Map::get_cur_object();
	AttachCube* cube;
	for(unsigned i=0;i<attach_cubes.size();i++){
		cube=attach_cubes.at(i);
		map->remove_cube(x+cube->x,y+cube->y,z+cube->z);
	}
}
bool CubeLarge::build(Map *map,int _x,int _y,int _z){
	x=_x,y=_y,z=_z;
	std::vector<math::vec3<int> > build_on;
	get_build_on(build_on);
	get_attach_cube(attach_cubes);

	AttachCube* cube;
	math::vec3<int>*on;
	for(unsigned i=0;i<build_on.size();i++){
		on=&(build_on.at(i));
		if(map->get_cube_type(x+on->x,y+on->y,z+on->x)<Cube::startcube){
			return false;
		}
	}
	for(unsigned i=0;i<attach_cubes.size();i++){
		cube=attach_cubes.at(i);
		if(map->get_cube_type(x+cube->x,y+cube->y,z+cube->x)!=Cube::cubeNull){
			return false;
		}
	}
	map->push_CubeEX(x,y,z,this);
	for(unsigned i=0;i<attach_cubes.size();i++){
		cube=attach_cubes.at(i);
		map->push_CubeEX(x+cube->x,y+cube->y,z+cube->x,cube);
	}
	//
	return true;

}
} /* namespace AOC */
