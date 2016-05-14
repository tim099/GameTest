#include "class/game/ageOfCube/map/MapDrawObject.h"
#include "class/display/model/Model.h"
#include <iostream>
MapDrawObject::MapDrawObject(std::string tex_str,std::string Nor_str){
	init(tex_str,Nor_str);

}
MapDrawObject::~MapDrawObject() {

}
void MapDrawObject::init(std::string tex_str,std::string Nor_str){
	init_drawObject("",tex_str,Nor_str,true);
	mat=math::vec4<float>(0.3,0.2,0.1,0.15);
}


