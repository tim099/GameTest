#include "class/game/map/MapDrawObject.h"
#include "class/display/model/Model.h"
#include <iostream>
MapDrawObject::MapDrawObject(std::string tex_str,std::string Nor_str){
	init(tex_str,Nor_str);

}
MapDrawObject::~MapDrawObject() {
	delete mapmodel;
	if(model_buffer)delete model_buffer;
}
void MapDrawObject::init(std::string tex_str,std::string Nor_str){
	init_drawObject("",tex_str,Nor_str,true);
	mapmodel=new Model(60,true);
	mat=glm::vec4(0.3,0.2,0.1,0.15);
	model_updated=false;
	map_updated=false;
	draw_map=false;
}
void MapDrawObject::clear_model_buffer(){
	if(model_buffer){
		delete model_buffer;
		model_buffer=0;
	}
}
void MapDrawObject::update_model_buffer(){
	if(!model_buffer){
		set_obj(new ModelBuffer(mapmodel));
	}else{
		model_buffer->load_model(mapmodel);
	}
	model_updated=false;
}
void MapDrawObject::update(){
	if(draw_map){
		if(model_updated||!model_buffer){
			update_model_buffer();
		}
	}else{
		clear_model_buffer();
	}
	draw_map=false;
}

