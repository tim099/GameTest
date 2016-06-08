#include "class/game/ageOfCube/map/cube/CubeLarge.h"
#include "class/game/ageOfCube/map/Map.h"
namespace AOC {

CubeLarge::CubeLarge() {
	x=0,y=0,z=0;removing=false;
}
CubeLarge::~CubeLarge() {

}
void CubeLarge::remove_cubeEX(){
	removing=true;
	Map *map=Map::get_cur_object();
	AttachCube* cube;
	for(unsigned i=0;i<attach_cubes.size();i++){
		cube=attach_cubes.at(i);
		if(!cube->removing){
			map->remove_cube(x+cube->x,y+cube->y,z+cube->z);
		}
	}
}
bool CubeLarge::buildable(int x,int y,int z){
	Map *map=Map::get_cur_object();
	std::vector<math::vec3<int> > build_on;
	std::vector<AttachCube*> attach_cubes;
	std::vector<int> build_on_type;

	get_build_on(build_on);
	get_attach_cube(attach_cubes);
	get_build_on_type(build_on_type);

	bool buildable=true;
	AttachCube* cube;
	math::vec3<int>*on;
	if(map->get_cube_type(x,y,z)!=Cube::cubeNull){
		buildable=false;
	}
	int type;
	bool flag;
	if(buildable){
		if(build_on_type.empty()){
			for(unsigned i=0;i<build_on.size();i++){
				on=&(build_on.at(i));
				type=map->get_cube_type(x+on->x,y+on->y,z+on->z);

				if(type<Cube::cube_start){
					buildable=false;
					break;
				}
			}
		}else{
			for(unsigned i=0;i<build_on.size();i++){
				on=&(build_on.at(i));
				type=map->get_cube_type(x+on->x,y+on->y,z+on->z);
				flag=false;
				for(unsigned i=0;i<build_on_type.size();i++){
					if(type==build_on_type.at(i)){
						flag=true;
						break;
					}
				}
				if(!flag){
					buildable=false;
					break;
				}
			}
		}

	}

	if(buildable){
		for(unsigned i=0;i<attach_cubes.size();i++){
			cube=attach_cubes.at(i);
			if(map->get_cube_type(x+cube->x,y+cube->y,z+cube->z)!=Cube::cubeNull){
				buildable=false;
				break;
			}
		}
	}
	for(unsigned i=0;i<attach_cubes.size();i++){
		delete attach_cubes.at(i);
	}
	attach_cubes.clear();
	return buildable;
}
bool CubeLarge::create_cube_large(int _x,int _y,int _z){
	Map *map=Map::get_cur_object();
	x=_x,y=_y,z=_z;
	if(!buildable(x,y,z))return false;
	for(unsigned i=0;i<attach_cubes.size();i++){
		std::cerr<<"CubeLarge::create_cube_large delete attach_cubes"<<std::endl;
		delete attach_cubes.at(i);
	}
	attach_cubes.clear();
	get_attach_cube(attach_cubes);

	map->push_CubeEX(x,y,z,this);
	AttachCube* cube;
	for(unsigned i=0;i<attach_cubes.size();i++){
		cube=attach_cubes.at(i);
		map->push_CubeEX(x+cube->x,y+cube->y,z+cube->z,cube);
	}
	return true;
}
} /* namespace AOC */
