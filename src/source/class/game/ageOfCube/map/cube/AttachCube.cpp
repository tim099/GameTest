#include "class/game/ageOfCube/map/cube/AttachCube.h"
#include "class/game/ageOfCube/map/cube/CubeLarge.h"
#include "class/game/ageOfCube/map/Map.h"
#include <iostream>
namespace AOC{
AttachCube::AttachCube(int _x,int _y,int _z,CubeLarge *_parent) {
	x=_x;y=_y;z=_z;parent=_parent;destructing=false;
}
AttachCube::~AttachCube() {
	//std::cout<<"AttachCube::~AttachCube() start"<<std::endl;
	destructing=true;
	if(!parent->destructing){
		std::cout<<"AttachCube::~AttachCube() delete parent"<<std::endl;
		Map *map=Map::get_cur_object();
		map->remove_cube(parent->x,parent->y,parent->z);
	}
	//std::cout<<"AttachCube::~AttachCube() end"<<std::endl;
}
}
