#include "class/display/render/Renderer.h"
#include "class/display/shader/Shader.h"
#include "class/display/shader/shader2D/Shader2D.h"
#include "class/display/light/LightControl.h"
#include "class/display/buffer/frameBuffer/FrameBuffer.h"
#include "class/display/draw/Draw.h"
#include "class/display/window/Window.h"
#include "class/input/mouse/Mouse.h"
#include "class/display/texture/texture2D/Texture2D.h"

#include "class/tim/file/File.h"
#include <cstdio>
#include <iostream>
Renderer::Renderer(LightControl* _lightControl,Draw *_d_obj,Window *_window,
		Camera *_camera,Mouse* _mouse,TextureMap *_texmap,double* _shadow_dis){
	lightControl=_lightControl;
	shadow_dis=_shadow_dis;
	d_obj=_d_obj;
	rendering=false;
	window=_window;

	//FBO=_FBO;
    FBO=new FrameBuffer(window->get_size());
    FBO->gen_color_texture(GL_RGBA,GL_RGBA,GL_UNSIGNED_BYTE,P_Linear);
    FBO->gen_color_texture(GL_RGB,GL_RGB,GL_UNSIGNED_BYTE,P_Linear);//just test!!
    FBO->gen_depth_texture(GL_DEPTH_COMPONENT32F,GL_DEPTH_COMPONENT,GL_FLOAT,P_Linear);

    FBO2=new FrameBuffer(window->get_size());
    FBO2->gen_color_texture(GL_RGBA,GL_RGBA,GL_UNSIGNED_BYTE,P_Linear);
    FBO2->gen_depth_texture(GL_DEPTH_COMPONENT32F,GL_DEPTH_COMPONENT,GL_FLOAT,P_Linear);

	camera=_camera;
	mouse=_mouse;
	texmap=_texmap;
	creat_shaders();


	//std::vector<std::string> files=Tim::File::get_all_files("files/texture/");
	//for(unsigned i=0;i<files.size();i++)std::cout<<files.at(i)<<std::endl;
}
Renderer::~Renderer() {
	//delete texarr;
	delete FBO;
	delete FBO2;
	delete shader2D;
	for(unsigned i=0;i<shaders.size();i++){
		delete shaders.at(i);
	}
}
void Renderer::creat_shaders(){
	shader2D=new Shader("Shader2D");
	shader2D->LoadShader("files/shader/2D/2D.vert","files/shader/2D/2D.frag");

	shader=new Shader("Basic");
	shader->LoadShader("files/shader/basic/Basic.vert",
			"files/shader/basic/Basic.geo",
			"files/shader/basic/Basic.frag");
	shaders.push_back(shader);

	shader=new Shader("NormalMapping");
	shader->LoadShader("files/shader/normalMapping/NormalMapping.vert",
			"files/shader/normalMapping/NormalMapping.geo",
			"files/shader/normalMapping/NormalMapping.frag");
	shaders.push_back(shader);

	shader=new Shader("LightScatter");
	shader->LoadShader("files/shader/lightScatter/LightScatter.vert",
			"files/shader/lightScatter/LightScatter.geo",
			"files/shader/lightScatter/LightScatter.frag");
	shaders.push_back(shader);
	switch_shader("NormalMapping");
}
void Renderer::switch_shader(std::string name){
	for(unsigned i=0;i<shaders.size();i++){
		if(name==shaders.at(i)->Name()){
			shader=shaders.at(i);
		}
	}
}
bool Renderer::Rendering()const{
	return rendering;
}
void Renderer::set_window(Window *_window){
	window=_window;
}
void Renderer::update_mouse_data(){
	mouse->get_world_space_pos(FBO,window->get_size(),glm::inverse(camera->view_matrix(window->aspect())));
}
void Renderer::render(){
	//std::cout<<"renderer render start"<<std::endl;
	window->render_on();
	rendering=true;

	d_obj->update();
    lightControl->gen_shadow(camera,*shadow_dis,d_obj);
    (shader)->active_shader();
	FBO->bind_buffer();
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);//clear buffer
    //sent uniform
    camera->sent_uniform((shader)->programID,FBO->aspect());
    lightControl->sent_uniform((shader),camera->pos);

    texmap->get_tex("texcube")->sent_uniform((shader),30,"cubetex");

    //start draw
    d_obj->draw((shader),shader2D);
	FrameBuffer::unbind_buffer(window->get_size());//start draw on window buffer
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);//clear window buffer

	FBO->color_textures.at(0)->draw_texture(shader2D,
			new DrawData2D(window->aspect(),1.0,glm::vec2(0,1.0),1.0));
	/*
	shader2D->Enable(SobelMode|AddOnMode);
	shader2D->sent_Uniform("sobel_dv",glm::vec2(250,120));
	FBO->depth_textures.at(0)->draw_texture(shader2D,
			new DrawData2D(window->aspect(),1.0,glm::vec2(0,1.0),1.0));
	shader2D->Disable(SobelMode|AddOnMode);
	*/
	update_mouse_data();

	rendering=false;

	//window->swap_buffer();
	window->render_off();//release thread using this window
	//std::cout<<"renderer render end"<<std::endl;
}
