#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "class/display/draw/object/DrawObject.h"
#include "class/display/buffer/Buffer.h"
#include "class/display/shader/Shader.h"
#include "class/display/texture/Texture.h"
#include <iostream>
DrawObject::DrawObject(BufferObject* _obj,Texture* _texture,Texture* _NormalMap,bool _layer_texture) {
	obj=_obj;
	texture=_texture;
	NormalMap=_NormalMap;
	draw_shadow=true;
	layer_texture=_layer_texture;
}
DrawObject::~DrawObject() {
	clear_drawdata();
	clear_temp_drawdata();
	if(obj->AutoDelete())delete obj;//if not AutoDelete() then let it handle by outside!!

}
void DrawObject::update(){

}
void DrawObject::set_obj(BufferObject *_obj){
	if(obj){
		if(obj->AutoDelete())delete obj;//handle by outside!!
	}
	obj=_obj;
}
void DrawObject::Model_veiw(GLuint programID,const glm::mat4 &M){
    glUniformMatrix4fv(glGetUniformLocation(programID,"M"),1,GL_FALSE,&(M[0][0]));
}
void DrawObject::clear_drawdata(){
	for(unsigned i=0;i<datas.size();i++){
		delete datas.at(i);
	}
	datas.clear();
}
unsigned DrawObject::temp_pos_num()const{
	return temp_datas.size();
}
void DrawObject::clear_temp_drawdata(){
	for(unsigned i=0;i<temp_datas.size();i++){
		delete temp_datas.at(i);
	}
	temp_datas.clear();
}
void DrawObject::push_drawdata(DrawDataObj* p){
	datas.push_back(p);
}
void DrawObject::push_temp_drawdata(DrawDataObj* p){
	temp_datas.push_back(p);
}
void DrawObject::draw_shadow_vec(Shader *shader,std::vector<DrawDataObj*> &data_v){

	DrawDataObj* data;
	for(unsigned i=0;i<data_v.size();i++){
		data=data_v.at(i);
		if(data->draw_shadow){
			Model_veiw(shader->programID,data->pos->PosMat());
			obj->draw(shader->programID);
		}
	}
}
void DrawObject::draw_vec(Shader *shader,std::vector<DrawDataObj*> &data_v){
	DrawDataObj* data;
	for(unsigned i=0;i<data_v.size();i++){
		data=data_v.at(i);
		data->prepare_to_draw(shader);
		Model_veiw(shader->programID,data->pos->PosMat());
		obj->draw(shader->programID);
		data->draw_end(shader);
	}
}
void DrawObject::draw_shadow_map(Shader *shader){
	if(!draw_shadow)return;
	obj->vtbuffer->bind_buffer();
	draw_shadow_vec(shader,datas);
	draw_shadow_vec(shader,temp_datas);
	glDisableVertexAttribArray(0);//vertexbuffer
}
void DrawObject::draw_object(Shader *shader){
	shader->active_shader();
	obj->bind_buffer(shader);
	if(texture){
		if(!layer_texture){//simple texture
			texture->sent_uniform(shader,0,"Texture");
		}else{
			texture->sent_uniform(shader,2,"TextureArr");
		}
	}
	if(NormalMap){
		shader->Enable(NormalMapping);
		if(!layer_texture){
			NormalMap->sent_uniform(shader,1,"NormalTexture");
		}else{
			NormalMap->sent_uniform(shader,3,"NormalTextureArr");
		}
	}
	draw_vec(shader,datas);
	draw_vec(shader,temp_datas);
	shader->DisableNormapping();
	//Buffer::disable_all_buffer();
}
