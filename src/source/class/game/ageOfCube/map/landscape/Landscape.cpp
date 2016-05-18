#include "class/game/ageOfCube/map/landscape/Landscape.h"
#include "class/game/ageOfCube/map/landscape/tree/Tree.h"
#include "class/game/ageOfCube/map/Map.h"
#include <cstdio>
namespace AOC{
void Landscape::landscape_pre_init(){

}
Landscape::Landscape() {

}
Landscape::~Landscape() {

}
void Landscape::save_landscape(FILE * file){

}
void Landscape::load_landscape(FILE * file){

}
bool Landscape::build(Map *map,int x,int y,int z){
	if(map->get_cube_type(x,y,z)==Cube::cubeNull){
		map->push_CubeEX(x,y,z,this);
		return true;
	}
	return false;
}
void Landscape::save_cubeEX(FILE * file){
	fprintf(file,"%s\n",get_name().c_str());
	save_landscape(file);
}
void Landscape::load_cubeEX(FILE * file){
	load_landscape(file);
}
}
