#include "class/display/light/LightControl.h"
#include "class/display/draw/Draw.h"
#include "class/display/shader/Shader.h"
#include "class/display/shader/shader2D/Shader2D.h"
#include "class/display/texture/texture2D/Texture2D.h"
#include "class/display/font/StringRenderer.h"
#include "class/display/font/TextureString.h"
#include "class/display/font/DrawDataStr.h"
#include "class/display/light/LightControl.h"
#include "class/display/buffer/frameBuffer/FrameBuffer.h"
#include "class/display/texture/AllTextures.h"
#include "class/input/mouse/Mouse.h"
#include "class/display/window/ViewPort.h"
#include <iostream>

Draw::Draw() {
	d_objsMutex=new Tim::Mutex();
	d_texsMutex=new Tim::Mutex();
	//strRenderer=new StringRenderer("files/texture/font/font.bmp");
	strRenderer=new StringRenderer("files/texture/font/font1.png");
	lightControl=0;
	camera=0;
	Enable3D=true;
}
Draw::~Draw() {
	delete d_objsMutex;
	delete d_texsMutex;
	delete strRenderer;

	while(!d_texs.empty()){
		delete d_texs.back();
		d_texs.pop_back();
	}
}
void Draw::set_lightControl(LightControl* _lightControl){
	lightControl=_lightControl;
}
void Draw::set_camera(Camera *_camera){
	camera=_camera;
}
void Draw::sent_shadow_uniform(Shader *shader){
	if(!lightControl){
		std::cerr<<"Draw::sent_shadow_uniform fail no lightControl"<<std::endl;
	}
	lightControl->sent_uniform(shader,camera->pos);
}
void Draw::gen_shadow(Shader *shaderShadowMapping){
	if(!lightControl){
		std::cerr<<"Draw::gen_shadow fail no lightControl"<<std::endl;
	}
	lightControl->gen_shadow(shaderShadowMapping,camera,this);
}
void Draw::draw3D(Shader *shader,Shader *shaderWater,Shader *shaderShadowMapping,
		Shader2D *shader2D,FrameBuffer *FBO,FrameBuffer *waterFBO){
	if(!Enable3D){
		shader->active_shader();
		FBO->bind_buffer();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	//clear buffer
		return;
	}
	gen_shadow(shaderShadowMapping);

	///*
	shader->active_shader();
	FBO->bind_buffer();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	//clear buffer
	//sent uniform
	AllTextures::get_cur_object()->get_cur_tex("test/texcube")->sent_uniform(shader, 30, "skybox");

	camera->sent_uniform(shader->programID, FBO->aspect());
	sent_shadow_uniform(shader);
    for(unsigned i=0;i<d_objs.size();i++){//100
    	d_objs.at(i)->draw_object(shader);//draw all obj
    }
/*
    waterFBO->bind_buffer();
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);    //clear window buffer
	//FBO->color_textures.at(0)->draw_texture(shader2D,
			//new DrawData2D(1.0, glm::vec2(0, 1.0), 1.0));
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	//clear buffer

    float water_height=30;
    //GLdouble h[4]={0,1.0,0,-water_height};
    //glCullFace(GL_FRONT);
    //glEnable(GL_CLIP_PLANE0);
    //glClipPlane(GL_CLIP_PLANE0,h);

	//sent uniform
	AllTextures::get_cur_object()->get_cur_tex("test/texcube")->sent_uniform(shader, 30, "skybox");
	Camera reflect_cam(camera);

	reflect_cam.pos.y-=2.0*(reflect_cam.pos.y-water_height);
	reflect_cam.look_at.y-=2.0*(reflect_cam.look_at.y-water_height);
	//reflect_cam.up.y=-1.0;
	reflect_cam.sent_uniform(shader->programID, waterFBO->aspect());
	sent_shadow_uniform(shader);
    for(unsigned i=0;i<d_objs.size();i++){//100
    	d_objs.at(i)->draw_object(shader);//draw all obj
    }
    //glDisable(GL_CLIP_PLANE0);
    //glCullFace(GL_BACK);

*/

	FBO->bind_buffer();
	//waterFBO->color_textures.at(0)->draw_texture(shader2D,
				//new DrawData2D(1.0, glm::vec2(0, 1.0), 0.3));

	shaderWater->active_shader();
	float time=glfwGetTime();
	shaderWater->sent_Uniform("waveTime",time);
	FBO->depth_textures.at(0)->sent_uniform(shaderWater,31,"scenedepthtex");
	waterFBO->color_textures.at(0)->sent_uniform(shaderWater,31,"reflecttex");
	//sent uniform
	AllTextures::get_cur_object()->get_cur_tex("test/texcube")->sent_uniform(shaderWater, 30, "skybox");

	camera->sent_uniform(shaderWater->programID, FBO->aspect());
	sent_shadow_uniform(shaderWater);
    for(unsigned i=0;i<water_d_objs.size();i++){//100
    	//std::cout<<"draw water"<<std::endl;
    	water_d_objs.at(i)->draw_object(shaderWater);//draw all obj
    }
    //glDisable(GL_BLEND);
	Mouse::get_cur_mouse()->get_world_space_pos(FBO,
			glm::inverse(camera->view_matrix(ViewPort::get_cur_window_aspect())));
	//*/
}
void Draw::draw2D(Shader2D *shader2D,FrameBuffer *FBO){
	FBO->bind_buffer();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	//clear buffer
    for(unsigned i=0;i<d_texs.size();i++){
    	d_texs.at(i)->draw(shader2D);
    }
    strRenderer->draw(shader2D);
}
void Draw::draw_shadow(Shader *shader){
    for(unsigned i=0;i<d_objs.size();i++){
    	d_objs.at(i)->draw_shadow_map(shader);//draw all obj
    }
}
void Draw::remove(DrawObject* obj){
	if(obj->get_type()=="WaterDrawObject"){
		for(unsigned i=0;i<water_d_objs.size();i++){
			if(water_d_objs.at(i)==obj){
				water_d_objs.at(i)=water_d_objs.back();
				water_d_objs.pop_back();
				return;
			}
		}
	}else{
		for(unsigned i=0;i<d_objs.size();i++){
			if(d_objs.at(i)==obj){
				d_objs.at(i)=d_objs.back();
				d_objs.pop_back();
				return;
			}
		}
	}

	std::cerr<<"Draw::remove(DrawObject* obj) fail,can't find obj:"<<obj<<std::endl;
}
void Draw::push(DrawObject* obj){
	d_objsMutex->wait_for_this();
	if(obj->get_type()=="WaterDrawObject"){
		//std::cout<<"push draw object alpha"<<std::endl;
		water_d_objs.push_back(obj);
	}else{
		d_objs.push_back(obj);
	}

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
    for(unsigned i=0;i<water_d_objs.size();i++){
    	water_d_objs.at(i)->update();
    }
}
void Draw::clear_tmp_data(){
    for(unsigned i=0;i<d_objs.size();i++){
    	d_objs.at(i)->clear_temp_drawdata();
    }
    for(unsigned i=0;i<water_d_objs.size();i++){
    	water_d_objs.at(i)->clear_temp_drawdata();
    }
    while(!d_texs.empty()){
    	delete d_texs.back();
    	d_texs.pop_back();
    }
    strRenderer->clear();
}

