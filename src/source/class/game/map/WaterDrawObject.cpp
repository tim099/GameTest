#include "class/game/map/WaterDrawObject.h"
#include "class/display/model/Model.h"
WaterDrawObject::WaterDrawObject() {
 init();
}
void WaterDrawObject::init(){
	init_drawObject("","","",false);
	watermodel=new Model(60,true);
	mat=glm::vec4(0.3,0.2,0.1,0.15);
	model_updated=false;
	water_updated=false;
	draw_water=false;
	draw_shadow=true;
	alpha_drawobject=true;
}
WaterDrawObject::~WaterDrawObject() {
	delete watermodel;
	if(model_buffer)delete model_buffer;
}
void WaterDrawObject::update_model_buffer(){
	if(!model_buffer){
		set_obj(new ModelBuffer(watermodel));
	}else{
		model_buffer->load_model(watermodel);
	}
	model_updated=false;
}
void WaterDrawObject::clear_model_buffer(){
	if(model_buffer){
		delete model_buffer;
		model_buffer=0;
	}
}
void WaterDrawObject::update(){
	if(draw_water){
		if(model_updated||!model_buffer){
			update_model_buffer();
		}
	}else{
		clear_model_buffer();
	}

	draw_water=false;
}
