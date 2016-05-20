/*
 * Tower.cpp
 *
 *  Created on: 2016¦~5¤ë14¤é
 *      Author: LukeWu
 */


#include "class/game/ageOfCube/map/building/tower/Tower.h"
#include "class/game/ageOfCube/map/Map.h"
#include "class/display/draw/drawObject/AllDrawObjects.h"
#include <cstdio>
#include <iostream>
namespace AOC{
void Tower::building_pre_init(){
	//std::cout<<"Tree::pre_init()"<<std::endl;
	tower_Drawobj=Display::AllDrawObjects::get_cur_object()->get("building/basic_cube_tower_1");
	//tree_Drawobj=AllDrawObjects::get_cur_object()->get("landscape/broadleaftree");
}
Tower::Tower() {
	tower_type=tower;
	tower_Drawobj=0;
	pos=0;
	size = 3.0;
}
Tower::Tower(Tower* tower) {
	tower_type=tower->tower_type;
	tower_Drawobj=tower->tower_Drawobj;
	pos=0;
	size = 6.0;
}
Tower::~Tower() {
	if(pos)delete pos;
	//std::cout<<"delete tree"<<std::endl;
}
void Tower::save_building(FILE * file){
	fprintf(file,"%c\n",(char)tower_type);
}
void Tower::load_building(FILE * file){
	fscanf(file,"%c\n",(char*)&tower_type);
}
void Tower::set_pos(int x,int y,int z){
	if(!pos){
		pos=new math::Position();
	}
	math::vec3<int> real_size=get_cube_large_size();
	pos->set_pos(glm::vec3(AOC::Map::CUBE_SIZE*x+0.5*real_size.x,
			AOC::Map::CUBE_SIZE*y+0.5*real_size.y,
			AOC::Map::CUBE_SIZE*z+0.5*real_size.z));
	pos->set_scale(glm::vec3(size,size,size));
}
void Tower::draw(){
	tower_Drawobj->push_temp_drawdata(new Display::DrawDataObj(pos));
	//std::cout<<"draw tree"<<std::endl;
}
}
