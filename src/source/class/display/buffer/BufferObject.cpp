#include "class/display/buffer/BufferObject.h"
#include "class/display/buffer/Buffer.h"
#include "class/display/model/Model.h"
#include "class/display/texture/Texture.h"
#include "class/display/shader/Shader.h"
#include <iostream>

BufferObject::BufferObject(Model *m,bool _auto_delete){
	vtbuffer=new Buffer(m->vtBuffer,m->vtdatasize(),0,3,GL_FLOAT);
	uvbuffer=new Buffer(m->uvBuffer,m->uvdatasize(),1,2,GL_FLOAT);
	vnbuffer=new Buffer(m->vnBuffer,m->vndatasize(),2,3,GL_FLOAT);
	if(m->lyBuffer){
		enable_lybuffer=true;
		lybuffer=new Buffer(m->lyBuffer,m->lydatasize(),3,1,GL_FLOAT);
	}else{
		enable_lybuffer=false;
		lybuffer=new Buffer(m->vtBuffer,m->lydatasize(),3,1,GL_FLOAT);//fake!!
	}
	vertex_num=m->vtlen();
	mat=m->mat;
	auto_delete=_auto_delete;																																																	auto_delete=_auto_delete;
}
BufferObject::~BufferObject() {
	delete vtbuffer;
	delete uvbuffer;
	delete vnbuffer;
	delete lybuffer;
}
bool BufferObject::AutoDelete()const{
	//will delete by draw object!!
	return auto_delete;
}
void BufferObject::bind_buffer(Shader *shader){
	vtbuffer->bind_buffer();
	uvbuffer->bind_buffer();
	vnbuffer->bind_buffer();
	lybuffer->bind_buffer();
	if(enable_lybuffer){
		shader->Enable(LayerTexture);//enable lybuffer
	}else{
		shader->Disable(LayerTexture);//disable lybuffer
	}

	glUniform4f(glGetUniformLocation(shader->programID,"mat"),mat.x,mat.y,mat.z,mat.w);
}
void BufferObject::draw(GLuint programID,GLenum mode){
	glDrawArrays(mode,0,vertex_num);
	//glDrawArrays(GL_LINES,0,vertex_num);
	//glDrawArrays(GL_POINTS,0,vertex_num);
}
