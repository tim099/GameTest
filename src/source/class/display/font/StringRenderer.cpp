#include "class/display/font/StringRenderer.h"
#include "class/display/texture/texture2D/Texture2D.h"
#include "class/display/shader/shader2D/Shader2D.h"
#include "class/display/buffer/Buffer.h"
#include "class/display/model/Vertex.h"
#include "class/display/buffer/Buffer.h"
#include "class/display/window/ViewPort.h"
#include <glm/glm.hpp>
#include <iostream>
namespace Display{
StringRenderer::StringRenderer(std::string fontTexturePath) {
	targetaspect = 0.0f;
	fontTexture = Texture2D::loadImage(fontTexturePath.c_str(), P_Linear);
	vtbuffer = new Buffer(0, 0, 0, 3, GL_FLOAT);
	uvbuffer = new Buffer(0, 0, 1, 2, GL_FLOAT);
}
StringRenderer::~StringRenderer() {
	delete fontTexture;
	delete vtbuffer;
	delete uvbuffer;
	clear();
}
void StringRenderer::clear() {
	while (!render_strs.empty()) {
		delete render_strs.back();
		render_strs.pop_back();
	}
}
void StringRenderer::push(RenderString* renderStr) {
	render_strs.push_back(renderStr);
}
void StringRenderer::render(Shader2D* shader2D, RenderString* render_str) {
	//std::cout<<"render string:"<<renderStr->str<<std::endl;
	float aspect = 1.0 / targetaspect;

	math::vec2<float> tsize = math::vec2<float>(
			Tim::Math::get_size(render_str->size, aspect));

	math::vec2<float> pos;
	Vertex::gen_quad_vt(vertex_buffer_data, glm::vec3(0, 0, 0),
			glm::vec3(tsize.x, tsize.y, 0), true);
	vtbuffer->update_buffer(vertex_buffer_data, sizeof(vertex_buffer_data));
	vtbuffer->bind_buffer();
	int col = 0, line = 0;
	unsigned c;
	math::vec2<float> render_pos = render_str->pos;
	if (render_str->render_at_middle) {
		math::vec2<float> str_size = render_str->string_size();
		render_pos += glm::vec2(-0.5 * str_size.x, 0.5*str_size.y/aspect);
	}
	for (unsigned i = 0; i < render_str->str.size(); i++) {
		pos = (render_pos
						+ math::vec2<float>(
								tsize.x * RenderString::Font_Interval
										* (col + 0.5) - 0.5,
								-tsize.y * (line + 0.5) - 0.5))*2.0f;

		shader2D->sent_Uniform("position", pos);
		c = render_str->str.at(i);
		switch (c) {
		case '\n':
			line++;
			col = 0;
			break;
		case '	':
			col += TAB_SIZE;
			break;
		default:
			col++;
			render_text(c);
		}
	}
	if(render_str->insert_at!=-1){
		col = 0, line = 0;
		for (unsigned i = 0; i < render_str->str.size()&&
		(int)i<render_str->insert_at; i++) {

			c = render_str->str.at(i);
			switch (c) {
			case '\n':
				line++;
				col = 0;
				break;
			case '	':
				col += TAB_SIZE;
				break;
			default:
				col++;
			}

		}
		pos = (render_pos+ math::vec2<float>(
						tsize.x * RenderString::Font_Interval
						* (col) - 0.5,
						-tsize.y * (line + 0.5) - 0.5))*2.0f;

		shader2D->sent_Uniform("position", pos);
		render_text('|');

	}
}
void StringRenderer::draw_string(Shader2D* shader2D,RenderString* renderStr){
	shader2D->active_shader();
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_DEPTH_TEST);
	shader2D->set_format(fontTexture->format);
	fontTexture->sent_uniform(shader2D, 0, "Texture");
	shader2D->sent_Uniform("alpha", 1.0f);
	targetaspect = ViewPort::get_cur_viewport_aspect();

	render(shader2D,renderStr);
	glEnable(GL_DEPTH_TEST);
	glDisable(GL_BLEND);
}
void StringRenderer::render_text(unsigned char c) {
	int x, y;
	x = c % 16;
	y = c / 16;
	static const float dx1 = 0.0f, dy1 = 0.001f;
	static const float dx2 = 0.0f, dy2 = -0.0005f;
	Vertex::gen_quad_uv(uv_buffer_data,
			glm::vec2(Font_seg * x - dx1 ,
					1.0 - Font_seg * (y + 1) + dy1 ),
			glm::vec2(Font_seg * (x + 1) + dx2 ,
					1.0 - (Font_seg * y) + dy2 ));
	uvbuffer->update_buffer(uv_buffer_data, sizeof(uv_buffer_data));
	uvbuffer->bind_buffer();
	glDrawArrays(GL_TRIANGLES, 0, 2 * 3); //2*3=two triangle
}
void StringRenderer::draw(Shader2D* shader2D) {
	shader2D->active_shader();
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_DEPTH_TEST);
	shader2D->set_format(fontTexture->format);
	fontTexture->sent_uniform(shader2D, 0, "Texture");
	shader2D->sent_Uniform("alpha", 1.0f);
	targetaspect = ViewPort::get_cur_viewport_aspect();

	for (unsigned i = 0; i < render_strs.size(); i++) {
		render(shader2D, render_strs.at(i));
	}
	glEnable(GL_DEPTH_TEST);
	glDisable(GL_BLEND);
}
}
