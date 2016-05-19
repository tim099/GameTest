#include "class/game/ageOfCube/map/cube/CubeLarge.h"
#include "class/game/ageOfCube/map/Map.h"
namespace AOC {

CubeLarge::CubeLarge() {
	x=0,y=0,z=0;removing=false;
}
CubeLarge::~CubeLarge() {

}
void CubeLarge::remove(){
	removing=true;
	Map *map=Map::get_cur_object();
	AttachCube* cube;
	for(unsigned i=0;i<attach_cubes.size();i++){
		cube=attach_cubes.at(i);
		if(!cube->removing)map->remove_cube(x+cube->x,y+cube->y,z+cube->z);
	}
}
bool CubeLarge::buildable(Map *map,int x,int y,int z){
	std::vector<math::vec3<int> > build_on;
	std::vector<AttachCube*> attach_cubes;
	get_build_on(build_on);
	get_attach_cube(attach_cubes);
	bool buildable=true;
	AttachCube* cube;
	math::vec3<int>*on;
	if(map->get_cube_type(x,y,z)!=Cube::cubeNull){
		buildable=false;
	}
	if(buildable){
		for(unsigned i=0;i<build_on.size();i++){
			on=&(build_on.at(i));
			if(map->get_cube_type(x+on->x,y+on->y,z+on->x)<Cube::startcube){
				buildable=false;
				break;
			}
		}
	}

	if(buildable){
		for(unsigned i=0;i<attach_cubes.size();i++){
			cube=attach_cubes.at(i);
			if(map->get_cube_type(x+cube->x,y+cube->y,z+cube->x)!=Cube::cubeNull){
				buildable=false;
				break;
			}
		}
	}
	for(unsigned i=0;i<attach_cubes.size();i++){
		delete attach_cubes.at(i);
	}
	return buildable;
}
bool CubeLarge::build(Map *map,int _x,int _y,int _z){
	x=_x,y=_y,z=_z;
	std::vector<math::vec3<int> > build_on;
	for(unsigned i=0;i<attach_cubes.size();i++){
		delete attach_cubes.at(i);
	}
	attach_cubes.clear();

	get_build_on(build_on);
	get_attach_cube(attach_cubes);

	AttachCube* cube;
	math::vec3<int>*on;
	if(map->get_cube_type(x,y,z)!=Cube::cubeNull)return false;
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
	return true;
}
} /* namespace AOC */
