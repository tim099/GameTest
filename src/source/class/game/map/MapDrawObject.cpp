#include "class/game/map/MapDrawObject.h"
#include "class/display/model/Model.h"
#include <iostream>
MapDrawObject::MapDrawObject(std::string tex_str,std::string Nor_str){
	//: DrawObject("",tex_str,Nor_str,true)
	init(tex_str,Nor_str);

}
MapDrawObject::~MapDrawObject() {
	delete mapmodel;
	delete obj;
}
void MapDrawObject::init(std::string tex_str,std::string Nor_str){
	init_drawObject("",tex_str,Nor_str,true);
	mapmodel=new Model(60,true);
	mat=glm::vec4(0.3,0.2,0.1,0.15);
	updated=false;
}
void MapDrawObject::update(){
	if(updated){
		if(!obj){
			set_obj(new ModelBuffer(mapmodel));
		}else{
			obj->load_model(mapmodel);
		}
		updated=false;
	}
}
void MapDrawObject::update_model(){
	updated=true;
}
