#include "class/game/ageOfCube/map/landscape/Landscape.h"
#include "class/game/ageOfCube/map/landscape/tree/Tree.h"

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
void Landscape::save_cubeEX(FILE * file){
	//fprintf(file,"%s\n",get_name().c_str());
	save_landscape(file);
}
void Landscape::load_cubeEX(FILE * file){
	load_landscape(file);
}
}
