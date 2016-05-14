#include "class/game/ageOfCube/map/building/Building.h"
#include "class/game/ageOfCube/map/building/tower/Tower.h"
#include <cstdio>
namespace AOC{
void Building::building_pre_init(){

}
Building::Building() {

}
Building::~Building() {

}
void Building::save_building(FILE * file){

}
void Building::load_building(FILE * file){

}
void Building::save_cubeEX(FILE * file){
	fprintf(file,"%s\n",get_name().c_str());
	save_building(file);
}
void Building::load_cubeEX(FILE * file){
	load_building(file);
}
}
