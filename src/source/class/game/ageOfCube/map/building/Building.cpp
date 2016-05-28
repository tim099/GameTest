#include "class/game/ageOfCube/map/building/Building.h"
#include "class/game/ageOfCube/map/building/tower/Tower.h"
#include "class/display/light/LightControl.h"
#include "class/display/draw/Draw.h"
#include "class/game/ageOfCube/map/Map.h"
#include <cstdio>
namespace AOC{
void Building::building_pre_init(){

}
Building::Building() {
	size=1.0;
}
Building::~Building() {

}
void Building::build_cube_large(){
	push_to_controller();//create when build success
}
void Building::save_cubeEX(FILE * file){
	save_unit(file);
	save_building(file);
}
void Building::load_cubeEX(FILE * file){
	load_unit(file);
	load_building(file);
}
void Building::unit_update(){
	building_update();
}
void Building::draw_buildable(Map *map,int x,int y,int z){
	set_pos(x,y,z);
	Display::CubeLight* building_light=new Display::CubeLight();
	if(buildable(map,x,y,z)){
		building_light->color=glm::vec3(0,1,0);
	}else{
		building_light->color=glm::vec3(1,0,0);
	}

	building_light->size=get_cube_large_size().x+0.01;
	building_light->pos=glm::vec3(
			  x*Map::CUBE_SIZE+0.49*building_light->size,
			  y*Map::CUBE_SIZE+0.49*building_light->size,
			  z*Map::CUBE_SIZE+0.49*building_light->size);
	Display::Draw::get_cur_object()->lightControl->push_temp_light(building_light);
	//draw();
}
}
