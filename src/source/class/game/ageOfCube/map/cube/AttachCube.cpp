#include "class/game/ageOfCube/map/cube/AttachCube.h"
#include "class/game/ageOfCube/map/cube/CubeLarge.h"
#include "class/game/ageOfCube/map/Map.h"
#include <iostream>
namespace AOC{
AttachCube::AttachCube(int _x,int _y,int _z,CubeLarge *_parent) {
	x=_x;y=_y;z=_z;parent=_parent;removing=false;
}
void AttachCube::remove_cubeEX(){
	removing=true;
	if(!parent->removing){
		Map::get_cur_object()->remove_cube(parent->x,parent->y,parent->z);
		//std::cout<<"AttachCube::remove() 1"<<std::endl;
		//parent->remove();
	}
}
CubeEX* AttachCube::get_real_cube(){
	return parent;
}
AttachCube::~AttachCube() {

	//std::cout<<"AttachCube::~AttachCube() end"<<std::endl;
}
}
