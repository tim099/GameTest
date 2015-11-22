#include "class/display/draw/Draw.h"
#include "class/display/shader/Shader.h"
#include <iostream>
Draw::Draw() {

}
Draw::~Draw() {
	while(!d_objs.empty()){
		delete d_objs.back();
		d_objs.pop_back();
	}
	while(!d_texs.empty()){
		delete d_texs.back();
		d_texs.pop_back();
	}
	while(!subdraw.empty()){
		delete subdraw.back();
		subdraw.pop_back();
	}
}
void Draw::draw(Shader *shader){
    for(unsigned i=0;i<d_objs.size();i++){
    	d_objs.at(i)->draw_object(shader);//draw all obj
    }
    for(unsigned i=0;i<subdraw.size();i++){
    	subdraw.at(i)->draw(shader);
    }
}
void Draw::draw_shadow(Shader *shader){
    for(unsigned i=0;i<d_objs.size();i++){
    	d_objs.at(i)->draw_shadow_map(shader->programID);//draw all obj
    }
    for(unsigned i=0;i<subdraw.size();i++){
    	subdraw.at(i)->draw_shadow(shader);
    }
}
void Draw::push(DrawObject* obj){
	d_objs.push_back(obj);
}
void Draw::push(DrawTexture* tex){
	d_texs.push_back(tex);
}
DrawObject* Draw::get_obj(unsigned i){
	return d_objs.at(i);
}
unsigned Draw::obj_size()const{
	return d_objs.size();
}
void Draw::clear_tmp_pos(){
    for(unsigned i=0;i<d_objs.size();i++){
    	d_objs.at(i)->clear_temp_position();
    }
    for(unsigned i=0;i<subdraw.size();i++){
    	subdraw.at(i)->clear_tmp_pos();
    }
}
void Draw::remove(DrawObject* obj){
	for(unsigned i=0;i<d_objs.size();i++){
		if(d_objs.at(i)==obj){
			d_objs.at(i)=d_objs.back();
			d_objs.pop_back();
			delete obj;
		}
	}
}
