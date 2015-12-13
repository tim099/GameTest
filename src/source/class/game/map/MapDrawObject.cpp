#include "class/game/map/MapDrawObject.h"
#include "class/display/model/Model.h"
#include <iostream>
MapDrawObject::MapDrawObject(BufferObject* obj,Texture* texture,Texture* NormalMap)
: DrawObject(obj,texture,NormalMap,true){
	mapmodel=new Model(60,true);
	mapmodel->mat=glm::vec4(0.3,0.2,0.1,0.15);
	updated=false;
}
MapDrawObject::~MapDrawObject() {
	delete mapmodel;
}
void MapDrawObject::update(){
	if(updated){
		set_obj(new BufferObject(mapmodel));
		updated=false;
	}
}
void MapDrawObject::update_model(){
	updated=true;
}
