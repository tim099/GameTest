#include "class/game/ageOfCube/map/cube/water/Water.h"
#include "class/game/ageOfCube/map/Map.h"
#include "class/display/draw/drawObject/AllDrawObjects.h"
#include <iostream>
namespace AOC{
Water::Water() {

}
Water::~Water() {
	//std::cout<<"delete water"<<std::endl;
}
void Water::update(int x,int y,int z,int ux,int uy,int uz){

	AOC::Map* map=AOC::Map::get_cur_object();
	if(!map){
		std::cerr<<"no map!!"<<std::endl;
		return;
	}
	///*
	if(map->get_cube_type(x,y-1,z)==Cube::cubeNull){//down
		//std::cout<<"water update1:"<<x<<","<<y-1<<","<<z<<std::endl;
		map->set_cube_type(x,y-1,z,Cube::water);
		//std::cout<<"water update end:"<<std::endl;
	}else if(map->get_cube_type(x+1,y,z)==Cube::cubeNull){//right
		//std::cout<<"water update2:"<<x+1<<","<<y<<","<<z<<std::endl;
		map->set_cube_type(x+1,y,z,Cube::water);
		//std::cout<<"water update end:"<<std::endl;
	}else if(map->get_cube_type(x-1,y,z)==Cube::cubeNull){//left
		//std::cout<<"water update3:"<<x-1<<","<<y<<","<<z<<std::endl;
		map->set_cube_type(x-1,y,z,Cube::water);
		//std::cout<<"water update end:"<<std::endl;
	}else if(map->get_cube_type(x,y,z+1)==Cube::cubeNull){//front
		//std::cout<<"water update4:"<<x<<","<<y<<","<<z+1<<std::endl;
		map->set_cube_type(x,y,z+1,Cube::water);
		//std::cout<<"water update end:"<<std::endl;
	}else if(map->get_cube_type(x,y,z-1)==Cube::cubeNull){//back
		//std::cout<<"water update5:"<<x<<","<<y<<","<<z-1<<std::endl;
		map->set_cube_type(x,y,z-1,Cube::water);
		//std::cout<<"water update end:"<<std::endl;
	}
	//*/
}
}
