#include "class/display/render/Renderer.h"
#include "class/display/shader/Shader.h"
#include "class/display/shader/shader2D/Shader2D.h"
#include "class/display/light/LightControl.h"
#include "class/display/buffer/frameBuffer/FrameBuffer.h"
#include "class/display/draw/Draw.h"
#include "class/display/window/Window.h"
#include "class/input/mouse/Mouse.h"
#include "class/display/texture/texture2D/Texture2D.h"
#include <cstdio>
#include <iostream>
Renderer::Renderer(LightControl* _lightControl,Draw *_d_obj,Window *_window,Shader **_shader,
		FrameBuffer *_FBO,Camera *_camera,Mouse* _mouse,TextureMap *_texmap,double* _shadow_dis){
	lightControl=_lightControl;
	shadow_dis=_shadow_dis;
	d_obj=_d_obj;
	rendering=false;
	window=_window;
	shader=_shader;
	FBO=_FBO;
	camera=_camera;
	mouse=_mouse;
	texmap=_texmap;
	shader2D=new Shader();
	shader2D->LoadShader("files/shader/2D/2D.vert","files/shader/2D/2D.frag");

	std::vector<std::string> path;
	path.push_back(std::string("files/texture/tes1.bmp"));
	path.push_back(std::string("files/texture/tes2.bmp"));
	path.push_back(std::string("files/texture/tes3.bmp"));
	texarr=Texture2DArr::gen_texture2DArr(path,glm::ivec3(256,256,3),GL_RGB,GL_RGB,GL_UNSIGNED_BYTE);
	//texarr=Texture2DArr::gen_texture2DArr(glm::ivec3(256,256,3),GL_RGB,GL_RGB,GL_UNSIGNED_BYTE);
	//texarr->bind_texture();
	//Image<unsigned char>::load_sub_image("files/texture/tes1.bmp",texarr->target,0);
	//Image<unsigned char>::load_sub_image("files/texture/tes2.bmp",texarr->target,1);
	//Image<unsigned char>::load_sub_image("files/texture/tes3.bmp",texarr->target,2);
}
Renderer::~Renderer() {
	delete texarr;
	delete shader2D;
}
bool Renderer::Rendering()const{
	return rendering;
}
void Renderer::render(){
	std::cout<<"renderer render start"<<std::endl;

	window->render_on();
	rendering=true;

	d_obj->update();
    lightControl->gen_shadow(camera,*shadow_dis,d_obj);
    (*shader)->active_shader();
	FBO->bind_buffer();
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);//clear buffer
    //sent uniform
    camera->sent_uniform((*shader)->programID,FBO->aspect());
    lightControl->sent_uniform((*shader),camera->pos);
    texarr->sent_uniform((*shader),30,"testarr");
    //lightControl->shadowData->SFBO->depth_textures.at(0)->sent_uniform((*shader),30,"testarr");
    //start draw
    d_obj->draw((*shader));

	FrameBuffer::unbind_buffer(window->get_size());//start draw on window buffer
	FBO->color_textures.at(0)->draw_texture(shader2D,window->aspect(),window->aspect(),1.0);

	mouse->get_world_space_pos(FBO,window->get_size(),glm::inverse(camera->view_matrix(window->aspect())));

	rendering=false;


	window->swap_buffer();
	window->render_off();//release thread using this window

	std::cout<<"renderer render end"<<std::endl;
}
