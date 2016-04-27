#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "class/display/draw/drawObject/DrawObject.h"
#include "class/display/buffer/Buffer.h"
#include "class/display/shader/Shader.h"
#include "class/display/texture/Texture.h"
#include "class/display/texture/AllTextures.h"
#include "class/display/model/modelBuffer/AllModelBuffers.h"


#include "class/display/draw/Draw.h"
#include <iostream>
namespace Display{
DrawObject::DrawObject(std::string _obj_str, std::string _tex_str,
		std::string _normalTex_str, bool _layer_texture) {
	init_drawObject(_obj_str, _tex_str, _normalTex_str, _layer_texture);
}
DrawObject::DrawObject(){
	model_buffer = 0;
	texture = 0;
	NormalMap = 0;
	draw_shadow = false;
	layer_texture = 0;
	alpha_drawobject=false;
	sky_map=false;
}
void DrawObject::init_drawObject(std::string _obj_str, std::string _tex_str,
		std::string _normalTex_str, bool _layer_texture) {
	if (_tex_str != "") {
		texture = AllTextures::get_cur_tex(_tex_str);
	} else {
		texture = 0;
	}
	if (_normalTex_str != "") {
		NormalMap = AllTextures::get_cur_tex(_normalTex_str);
	} else {
		NormalMap = 0;
	}
	if(_obj_str!=""){
		model_buffer=AllModelBuffers::get_cur_model(_obj_str);
	}else{
		model_buffer=0;
	}
	init_drawObject(model_buffer, texture, NormalMap, _layer_texture);
}
void DrawObject::init_drawObject(ModelBuffer* _obj, Texture* _texture,
		Texture* _NormalMap, bool _layer_texture) {
	model_buffer = _obj;
	texture = _texture;
	NormalMap = _NormalMap;
	draw_shadow = true;
	layer_texture = _layer_texture;
	mat = glm::vec4(0.3, 0.4, 0.01, 0.15); //x=diffuse,y=specular_value,z=ambient,w=emissive
	/*
	Draw* cur_draw=Draw::get_cur_object();
	if(cur_draw){
		cur_draw->push(this);
	}else{
		std::cerr<<"cur Draw is not exist!!can't initialize DrawObject"<<std::endl;
	}
	*/
}
DrawObject::~DrawObject() {
	//std::cout << "delete draw object" << std::endl;
	clear_temp_drawdata();
	/*
	Draw* cur_draw=Draw::get_cur_object();
	if(cur_draw){
		cur_draw->remove(this);
	}else{
		std::cerr<<"cur \"Draw\" object is not exist!!can't remove DrawObject"<<std::endl;
	}
	*/
}
void DrawObject::update() {

}
void DrawObject::set_obj(ModelBuffer *_obj) {
	model_buffer = _obj;
}
void DrawObject::sent_model_veiw_uniform(GLuint programID, const glm::mat4 &M) {
	glUniformMatrix4fv(glGetUniformLocation(programID, "M"), 1, GL_FALSE,
			&(M[0][0]));
}
unsigned DrawObject::temp_pos_num() const {
	return temp_datas.size();
}
void DrawObject::clear_temp_drawdata() {
	for (unsigned i = 0; i < temp_datas.size(); i++) {
		delete temp_datas.at(i);
	}
	temp_datas.clear();
}
void DrawObject::push_temp_drawdata(DrawDataObj* p) {
	temp_datas.push_back(p);
}
void DrawObject::draw_shadow_vec(Shader *shader,
		std::vector<DrawDataObj*> &data_v) {
	DrawDataObj* data;
	for (unsigned i = 0; i < data_v.size(); i++) {
		data = data_v.at(i);
		if (data->draw_shadow) {
			sent_model_veiw_uniform(shader->programID, data->pos->PosMat());
			model_buffer->draw(shader->programID);
		}
	}
}
void DrawObject::draw_vec(Shader *shader, std::vector<DrawDataObj*> &data_v) {
	DrawDataObj* data;
	for (unsigned i = 0; i < data_v.size(); i++) {
		data = data_v.at(i);
		data->prepare_to_draw(shader);
		sent_model_veiw_uniform(shader->programID, data->pos->PosMat());
		model_buffer->draw(shader->programID);
		data->draw_end(shader);
	}
}
void DrawObject::draw_shadow_map(Shader *shader) {
	if (!draw_shadow)return;
	if(temp_datas.empty())return;
	model_buffer->vtbuffer->bind_buffer();
	draw_shadow_vec(shader, temp_datas);
	model_buffer->vtbuffer->unbind_buffer();
}
void DrawObject::draw_object(Shader *shader) {
	if(temp_datas.empty())return;
	//shader->active_shader();
	model_buffer->bind_buffer(shader);
	glUniform4f(glGetUniformLocation(shader->programID, "mat"), mat.x, mat.y,
			mat.z, mat.w);
	if(alpha_drawobject){
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
		//glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_DST_ALPHA);
	}
	if(sky_map){
		shader->Enable(SkyMap);
	}
	if (texture) {
		if(texture->format==GL_RGBA){
			shader->Enable(AlphaTexture);
		}
		if (!layer_texture) { //simple texture
			texture->sent_uniform(shader, 0, "Texture");
		} else {
			texture->sent_uniform(shader, 2, "TextureArr");
		}
	}
	if (NormalMap) {
		shader->Enable(NormalMapping);
		if (!layer_texture) {
			NormalMap->sent_uniform(shader, 1, "NormalTexture");
		} else {
			NormalMap->sent_uniform(shader, 3, "NormalTextureArr");
		}
	}
	draw_vec(shader, temp_datas);
	model_buffer->unbind_buffer(shader);
	shader->Disable(SkyMap);
	shader->Disable(NormalMapping);
	shader->Disable(AlphaTexture);
	if (alpha_drawobject){
		glDisable(GL_BLEND);
	}

	//Buffer::disable_all_buffer();
}
}
