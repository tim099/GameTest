#include "class/display/buffer/BufferObject.h"
#include "class/display/buffer/Buffer.h"
#include "class/display/model/Model.h"
#include "class/display/texture/Texture.h"
#include <iostream>
BufferObject::BufferObject(GLuint _vtbuffer,GLuint _uvbuffer,GLuint _texturebuffer
		,GLuint _nbuffer,int _vertex_num,glm::vec4 _mat){
	vtbuffer=_vtbuffer;
	uvbuffer=_uvbuffer;
	vnbuffer=_nbuffer;
	vertex_num=_vertex_num;
	mat=_mat;
	auto_delete=true;
}
BufferObject::BufferObject(Model *m,bool _auto_delete){
	vtbuffer=Buffer::gen_buffer(m->vtBuffer,m->vtdatasize());
	uvbuffer=Buffer::gen_buffer(m->uvBuffer,m->uvdatasize());
	vnbuffer=Buffer::gen_buffer(m->vnBuffer,m->vndatasize());
	vertex_num=m->vtlen();
	mat=m->mat;
	auto_delete=_auto_delete;
}
BufferObject::~BufferObject() {
	//std::cout<<"vtbuffer"<<vtbuffer<<std::endl;
    glDeleteBuffers(1,&vtbuffer);
    //std::cout<<"uvbuffer"<<uvbuffer<<std::endl;
    glDeleteBuffers(1,&uvbuffer);
    //std::cout<<"vnbuffer"<<vnbuffer<<std::endl;
    glDeleteBuffers(1,&vnbuffer);
    //std::cout<<"delete BufferObject end"<<std::endl;
}
bool BufferObject::AutoDelete()const{
	//will delete by draw object!!
	return auto_delete;
}
void BufferObject::bind_buffer(GLuint programID){
	Buffer::bind_vtbuffer(vtbuffer);
	Buffer::bind_uvbuffer(uvbuffer);
	Buffer::bind_vnbuffer(vnbuffer);
	glUniform4f(glGetUniformLocation(programID,"mat"),mat.x,mat.y,mat.z,mat.w);
}
void BufferObject::draw(GLuint programID){
	glDrawArrays(GL_TRIANGLES,0,vertex_num);
	//glDrawArrays(GL_LINES,0,vertex_num);
	//glDrawArrays(GL_POINTS,0,vertex_num);
}
