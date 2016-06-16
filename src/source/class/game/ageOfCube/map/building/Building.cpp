#include "class/game/ageOfCube/map/building/Building.h"
#include "class/game/ageOfCube/map/building/tower/Tower.h"
#include "class/display/light/LightControl.h"
#include "class/display/draw/Draw.h"
#include "class/game/ageOfCube/map/Map.h"
#include "class/physic/RigidBody.h"
#include <cstdio>
namespace AOC{
void Building::building_pre_init(){

}
Building::Building() {
	//std::cout<<"Building::Building()="<<this<<std::endl;
	size=1.0;
	rotate=0;
	build_cost = ResourceModifier("cube",0);
}
Building::~Building() {
	//std::cout<<"Building::~Building()="<<this<<std::endl;
}
void Building::set_size(float _size){
	//pos.set_scale(glm::vec3(0.9*size,0.9*size,0.9*size));
	size=_size;
	building_set_pos(x,y,z);
}
math::vec3<double> Building::get_size(){
	return math::vec3<double>(get_cube_large_size().x*Map::CUBE_SIZE,
			get_cube_large_size().y*Map::CUBE_SIZE,
			get_cube_large_size().z*Map::CUBE_SIZE);
}
void Building::set_rotate(int _rotate){
	rotate=_rotate;
	pos.set_r(glm::vec3(0,90*rotate,0));

}
void Building::set_pos(int _x,int _y,int _z){

	pos.set_r(glm::vec3(0,90*rotate,0));
	x=_x,y=_y,z=_z;
	building_set_pos(_x,_y,_z);
}
void Building::building_set_pos(int x,int y,int z){
	math::vec3<int> real_size=get_cube_large_size();
	pos.set_pos(glm::vec3(AOC::Map::CUBE_SIZE*x+0.5*real_size.x,
			AOC::Map::CUBE_SIZE*y+0.5*real_size.y,
			AOC::Map::CUBE_SIZE*z+0.5*real_size.z));
	pos.set_scale(glm::vec3(size,size,size));
}
math::vec3<double> Building::get_rotate(){
	return math::vec3<double>(0,90*rotate,0);
}
math::vec3<double> Building::get_pos(){
	return math::vec3<double>(x*Map::CUBE_SIZE,y*Map::CUBE_SIZE,z*Map::CUBE_SIZE);
}
math::vec3<double> Building::get_mid_pos(){
	math::vec3<int>pos=get_pos_int();
	return math::vec3<double>(
			(pos.x+0.5*get_cube_large_size().x)*Map::CUBE_SIZE,
			(pos.y+0.5*get_cube_large_size().y)*Map::CUBE_SIZE,
			(pos.z+0.5*get_cube_large_size().z)*Map::CUBE_SIZE);
}
math::vec3<int> Building::get_pos_int(){
	return math::vec3<int>(x,y,z);
}
math::vec3<int> Building::get_mid_pos_int(){
	return math::vec3<int>(
			x+(get_cube_large_size().x-1)/2,
			y+(get_cube_large_size().y-1)/2,
			z+(get_cube_large_size().z-1)/2);
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
	if(buildable(x,y,z)){
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
void Building::draw(){
	draw_unit();
	draw_hp();
	draw_building();
}
bool Building::create_building(){
	bool build_success=create_cube_large(x,y,z);
	if(build_success){
		create_unit();
	}else{
		std::cerr<<"Building::build() fail"<<std::endl;
	}
	return build_success;
}
void Building::draw_hp(){
	if(get_hp()<get_max_hp()){
		Display::CubeLight* building_light=new Display::CubeLight();
		building_light->color=glm::vec3(3,0,0);


		building_light->cube_size=glm::vec3(
				Map::CUBE_SIZE*1.0*get_cube_large_size().x,
				Map::CUBE_SIZE*1.0*get_cube_large_size().y*
				((get_max_hp()-get_hp())/(double)get_max_hp()),

				Map::CUBE_SIZE*1.0*get_cube_large_size().z);

		building_light->pos=glm::vec3(
				  x*Map::CUBE_SIZE+0.49*building_light->cube_size.x,
				  y*Map::CUBE_SIZE+0.49*building_light->cube_size.y,
				  z*Map::CUBE_SIZE+0.49*building_light->cube_size.z);
		Display::Draw::get_cur_object()->lightControl->push_temp_light(building_light);
	}
}

void Building::upgrade_building(std::string description){
	if(description == "fire_upgrade"){
		//std::cout<<"fire upgrade"<<std::endl;
		//attack_alter(1.0);
		upgrade("fire", 1);
	}
	else if(description == "water_upgrade"){
		//std::cout<<"water upgrade"<<std::endl;
		max_hp_alter(50);
		upgrade("water", 1);
	}
	else if(description == "earth_upgrade"){
		//std::cout<<"earth upgrade"<<std::endl;
		armor_alter(1.0);
		upgrade("earth", 1);

	}
	else if(description == "air_upgrade"){
		//std::cout<<"air upgrade"<<std::endl;
		attack_cycle_alter(-1.0);
		upgrade("air", 1);
	}
}

}
