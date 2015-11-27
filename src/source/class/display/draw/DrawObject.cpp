#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "class/display/draw/DrawObject.h"
#include "class/display/buffer/Buffer.h"
#include "class/display/shader/Shader.h"
#include "class/display/texture/Texture.h"
#include <iostream>
DrawObject::DrawObject(BufferObject* _obj,Texture* _texture,Texture* _NormalMap) {
	obj=_obj;
	texture=_texture;
	NormalMap=_NormalMap;
	draw_shadow=true;
}
DrawObject::~DrawObject() {
	clear_position();
	clear_temp_position();
	if(obj){
		if(obj->AutoDelete())delete obj;//handle by outside!!
	}
}
void DrawObject::update(){

}
void DrawObject::set_obj(BufferObject *_obj){
	if(obj){
		if(obj->AutoDelete())delete obj;//handle by outside!!
	}
	obj=_obj;
}
void DrawObject::Model_veiw(GLuint programID,glm::mat4 M){
    glUniformMatrix4fv(glGetUniformLocation(programID,"M"),1,GL_FALSE,&(M[0][0]));
}
void DrawObject::clear_position(){
	for(unsigned i=0;i<m_pos.size();i++){
		delete m_pos.at(i);
	}
	m_pos.clear();
}
unsigned DrawObject::temp_pos_num()const{
	return temp_pos.size();
}
void DrawObject::clear_temp_position(){
	for(unsigned i=0;i<temp_pos.size();i++){
		delete temp_pos.at(i);
	}
	temp_pos.clear();
}
Position* DrawObject::push_position(Position* p){
	m_pos.push_back(p);
	return p;
}
Position* DrawObject::push_temp_position(Position* p){
	temp_pos.push_back(p);
	return p;
}
void DrawObject::draw_vec(GLuint programID,std::vector<Position*> &pos_v){
	for(unsigned i=0;i<pos_v.size();i++){
		Model_veiw(programID,pos_v.at(i)->PosMat());
		obj->draw(programID);
	}
}
void DrawObject::draw_shadow_map(GLuint programID){
	if(!draw_shadow)return;
	Buffer::bind_vtbuffer(obj->vtbuffer);
	draw_vec(programID,m_pos);
	draw_vec(programID,temp_pos);
	glDisableVertexAttribArray(0);//vertexbuffer
}
void DrawObject::draw_object(Shader *shader){
	obj->bind_buffer(shader->programID);
	texture->sent_uniform(shader,0,"myTextureSampler");
	if(NormalMap){
		shader->EnableNormapping();
		NormalMap->sent_uniform(shader,1,"NormalTexture");
	}
	draw_vec(shader->programID,m_pos);
	draw_vec(shader->programID,temp_pos);
	shader->DisableNormapping();
	Buffer::disable_all_buffer();
}
