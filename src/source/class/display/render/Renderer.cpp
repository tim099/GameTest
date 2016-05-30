#include "class/display/render/Renderer.h"
#include "class/display/shader/Shader.h"
#include "class/display/shader/shader2D/Shader2D.h"
#include "class/display/buffer/frameBuffer/FrameBuffer.h"
#include "class/display/draw/Draw.h"
#include "class/display/window/Window.h"
#include "class/display/texture/texture2D/Texture2D.h"
#include "class/tim/file/File.h"
#include "class/display/window/ViewPort.h"
#include "class/display/camera/Camera.h"
#include "class/input/mouse/Mouse.h"
#include "class/display/texture/texture2D/drawDataEX/SobelData.h"
#include <cstdio>
#include <iostream>
namespace Display{
Renderer::Renderer(Draw *_d_obj, Window *_window) {

	draw = _d_obj;
	rendering = false;
	window = _window;
	VertexArrayID = Buffer::GenVertexArray();

	FBO3D = new FrameBuffer(window->get_size());
	FBO3D->gen_color_texture(GL_RGBA, GL_RGBA, GL_UNSIGNED_BYTE, P_Linear);
	//FBO->gen_color_texture(GL_RGB, GL_RGB, GL_UNSIGNED_BYTE, P_Linear); //just test!!
	FBO3D->gen_depth_texture(GL_DEPTH_COMPONENT32F, GL_DEPTH_COMPONENT, GL_FLOAT,
			P_Linear);

	FBO2D = new FrameBuffer(window->get_size());
	FBO2D->gen_color_texture(GL_RGBA, GL_RGBA, GL_UNSIGNED_BYTE, P_Linear);
	FBO2D->gen_depth_texture(GL_DEPTH_COMPONENT32F, GL_DEPTH_COMPONENT, GL_FLOAT,
			P_Linear);
	waterReflectFBO = new FrameBuffer(window->get_size());
	waterReflectFBO->gen_color_texture(GL_RGBA, GL_RGBA, GL_UNSIGNED_BYTE, P_Linear);
	waterReflectFBO->gen_depth_texture(GL_DEPTH_COMPONENT32F, GL_DEPTH_COMPONENT, GL_FLOAT,
			P_Linear);
	waterRefractFBO = new FrameBuffer(window->get_size());
	waterRefractFBO->gen_color_texture(GL_RGBA, GL_RGBA, GL_UNSIGNED_BYTE, P_Linear);
	waterRefractFBO->gen_depth_texture(GL_DEPTH_COMPONENT32F, GL_DEPTH_COMPONENT, GL_FLOAT,
			P_Linear);
	creat_shaders();
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	//wglSwapIntervalEXT(1);
	//std::vector<std::string> files=Tim::File::get_all_files("files/texture/");
	//for(unsigned i=0;i<files.size();i++)std::cout<<files.at(i)<<std::endl;
}
Renderer::~Renderer() {
	//delete texarr;
	delete FBO3D;
	delete FBO2D;
	delete waterReflectFBO;
	delete waterRefractFBO;
	delete shader2D;
	delete shaderShadowMapping;
	delete shaderWater;
	for (unsigned i = 0; i < shaders.size(); i++) {
		delete shaders.at(i);
	}
	glDeleteVertexArrays(1, &VertexArrayID);
}

void Renderer::set_window(Window *_window) {
	window = _window;
}
void Renderer::creat_shaders() {
	shader2D = new Shader2D("Shader2D");
	shader2D->LoadShader("files/shader/2D/2D.vert", "files/shader/2D/2D.frag");

	shaderShadowMapping=new Shader();
	shaderShadowMapping->LoadShader("files/shader/shadow/MultiShadowCommon.vert",
			"files/shader/shadow/multiShadowMapping/MultiShadowMapping.geo",
			"files/shader/shadow/MultiShadowCommon.frag");

	shaderWater=new Shader();
	shaderWater->LoadShader("files/shader/water/water.vert",
				"files/shader/water/water.geo",
				"files/shader/water/water.frag");

	shader = new Shader("Basic");
	shader->LoadShader("files/shader/basic/Basic.vert",
			"files/shader/basic/Basic.geo", "files/shader/basic/Basic.frag");
	shaders.push_back(shader);

	shader = new Shader("NormalMapping");
	shader->LoadShader("files/shader/normalMapping/NormalMapping.vert",
			"files/shader/normalMapping/NormalMapping.geo",
			"files/shader/normalMapping/NormalMapping.frag");
	shaders.push_back(shader);

	shader = new Shader("LightScatter");
	shader->LoadShader("files/shader/lightScatter/LightScatter.vert",
			"files/shader/lightScatter/LightScatter.geo",
			"files/shader/lightScatter/LightScatter.frag");
	shaders.push_back(shader);
	switch_shader("NormalMapping");
}
void Renderer::switch_shader(std::string name) {
	for (unsigned i = 0; i < shaders.size(); i++) {
		if (name == shaders.at(i)->Name()) {
			shader = shaders.at(i);
		}
	}
}
bool Renderer::Rendering() const {
	return rendering;
}
void Renderer::render() {
	//std::cout<<"renderer render start"<<std::endl;

	//window->render_on();
	rendering = true;

	draw->update();

	draw->draw3D(shader,shaderWater,shaderShadowMapping,shader2D,FBO3D,
			waterReflectFBO,waterRefractFBO);

	draw->draw2D(shader2D,FBO2D);

	FrameBuffer::unbind_buffer(window->get_size()); //start draw on window buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);    //clear window buffer

	//draw 3D
	DrawData2D* data_2d;

	data_2d=new DrawData2D(1.0, glm::vec2(0, 1.0), 1.0);
	//data_2d->push_ex_data(new Display::drawDataEX::SobelData(0.3,0.5));
	FBO3D->color_textures.at(0)->draw_texture(shader2D,data_2d);

	/*
	shader2D->Enable(SobelMode | AddOnMode);
	shader2D->sent_Uniform("sobel_dv", glm::vec2(250, 120));
	FBO->depth_textures.at(0)->draw_texture(shader2D,
			new DrawData2D(1.0, glm::vec2(0, 1.0), 1.0));
	shader2D->Disable(SobelMode | AddOnMode);
	*/
	//draw 2D
	data_2d=new DrawData2D(1.0, glm::vec2(0, 1.0), 1.0);
	FBO2D->color_textures.at(0)->draw_texture(shader2D,data_2d);

	rendering = false;
	//window->swap_buffer();
	//window->render_off();    //release thread using this window
	//std::cout<<"renderer render end"<<std::endl;
}
}
