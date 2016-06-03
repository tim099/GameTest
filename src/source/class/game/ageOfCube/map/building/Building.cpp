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
	rotate=0;
}
Building::~Building() {

}
void Building::set_size(float _size){
	//pos.set_scale(glm::vec3(0.9*size,0.9*size,0.9*size));
	size=_size;
	building_set_pos(x,y,z);
}
void Building::set_rotate(int _rotate){
	rotate=_rotate;
	pos.set_r(glm::vec3(0,90*rotate,0));

}
void Building::set_pos(int _x,int _y,int _z){
	if(rotate!=0){
		pos.set_r(glm::vec3(0,90*rotate,0));
	}
	x=_x,y=_y,z=_z;
	building_set_pos(_x,_y,_z);
}
void Building::build_cube_large(){
	push_to_controller();//create when build success
}
void Building::save_cubeEX(FILE * file){
	fprintf(file,"%d %f\n",rotate,size);
	save_unit(file);
	save_building(file);
}
void Building::load_cubeEX(FILE * file){
	fscanf(file,"%d %f\n",&rotate,&size);
	load_unit(file);
	load_building(file);
}
void Building::unit_update(){
	building_update();
}
void Building::draw_buildable(Map *map){
	//set_pos(x,y,z);
	Display::CubeLight* building_light=new Display::CubeLight();
	if(buildable(map,x,y,z)){
		building_light->color=glm::vec3(0,1,0);
	}else{
		building_light->color=glm::vec3(1,0,0);
	}

	building_light->cube_size=glm::vec3(
			Map::CUBE_SIZE*1.05*get_cube_large_size().x,
			Map::CUBE_SIZE*1.05*get_cube_large_size().y,
			Map::CUBE_SIZE*1.05*get_cube_large_size().z);
	building_light->pos=glm::vec3(
			  x*Map::CUBE_SIZE+0.49*building_light->cube_size.x,
			  y*Map::CUBE_SIZE+0.49*building_light->cube_size.y,
			  z*Map::CUBE_SIZE+0.49*building_light->cube_size.z);
	Display::Draw::get_cur_object()->lightControl->push_temp_light(building_light);
	draw();
}
}
