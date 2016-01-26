#include "class/display/draw/Draw.h"
#include "class/display/shader/Shader.h"
#include "class/display/shader/shader2D/Shader2D.h"
#include "class/display/font/StringRenderer.h"
#include "class/display/font/TextureString.h"
#include "class/display/font/DrawDataStr.h"
//#include "class/display/texture/texture2D/drawDataEX/ColorAlter.h"
#include <iostream>
Draw::Draw() {
	d_objsMutex=new Tim::Mutex();
	d_texsMutex=new Tim::Mutex();
	//strRenderer=new StringRenderer("files/texture/font/font.bmp");
	strRenderer=new StringRenderer("files/texture/font/font1.png");
}
Draw::~Draw() {
	delete d_objsMutex;
	delete d_texsMutex;
	delete strRenderer;
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
void Draw::draw2D(Shader2D *shader2D,double targetaspect){
    for(unsigned i=0;i<d_texs.size();i++){
    	d_texs.at(i)->draw(shader2D);
    }
    strRenderer->draw(shader2D);
}
void Draw::draw_shadow(Shader *shader){
    for(unsigned i=0;i<d_objs.size();i++){
    	d_objs.at(i)->draw_shadow_map(shader);//draw all obj
    }
    for(unsigned i=0;i<subdraw.size();i++){
    	subdraw.at(i)->draw_shadow(shader);
    }
}
void Draw::push(DrawObject* obj){
	d_objsMutex->wait_for_this();
	d_objs.push_back(obj);
	d_objsMutex->release();
}
void Draw::push(DrawTexture* tex){
	d_texsMutex->wait_for_this();
	d_texs.push_back(tex);
	d_texsMutex->release();
}
void Draw::push(RenderString* renderStr){
	//std::cout<<"push "<<renderStr->str<<std::endl;
	strRenderer->push(renderStr);
}
DrawData* Draw::push_as_tex(RenderString* renderStr){
	//std::cout<<"push as tex"<<renderStr->str<<std::endl;
	TextureString *tex=new TextureString();
	DrawDataStr *data=new DrawDataStr(strRenderer,renderStr);

	DrawTexture* draw_tex=new DrawTexture(tex,data);

	push(draw_tex);
	return data;
}
DrawObject* Draw::get_obj(unsigned i){
	return d_objs.at(i);
}
unsigned Draw::obj_size()const{
	return d_objs.size();
}
void Draw::update(){
    for(unsigned i=0;i<d_objs.size();i++){
    	d_objs.at(i)->update();
    }
    for(unsigned i=0;i<subdraw.size();i++){
    	subdraw.at(i)->update();
    }
}
void Draw::clear_tmp_pos(){
    for(unsigned i=0;i<d_objs.size();i++){
    	d_objs.at(i)->clear_temp_drawdata();
    }
    for(unsigned i=0;i<subdraw.size();i++){
    	subdraw.at(i)->clear_tmp_pos();
    }
    while(!d_texs.empty()){
    	delete d_texs.back();
    	d_texs.pop_back();
    }
    strRenderer->clear();
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
