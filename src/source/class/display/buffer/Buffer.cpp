#include "class/display/buffer/Buffer.h"
#include <iostream>
Buffer::Buffer(GLfloat* data,int datasize,GLuint _index,GLint _size,GLenum _type,GLboolean _normalized
		,GLsizei _stride) {
	buffer=gen_buffer(data,datasize);
	index=_index;
	size=_size;
	type=_type;
	normalized=_normalized;
	stride=_stride;
}
Buffer::~Buffer() {

}
GLuint Buffer::gen_buffer(GLfloat* data,int size){
	GLuint buffer;
	glGenBuffers(1,&buffer);
	glBindBuffer(GL_ARRAY_BUFFER,buffer);
	glBufferData(GL_ARRAY_BUFFER,size,data,GL_STATIC_DRAW);
	return buffer;
}
GLuint Buffer::GenVertexArray(){
    GLuint VertexArrayID;
    glGenVertexArrays(1,&VertexArrayID);
    glBindVertexArray(VertexArrayID);
    return VertexArrayID;
}
void Buffer::bind_vtbuffer(GLuint vertexbuffer){
	glBindBuffer(GL_ARRAY_BUFFER,vertexbuffer);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,0,NULL);
}
void Buffer::bind_uvbuffer(GLuint uvbuffer){
	glBindBuffer(GL_ARRAY_BUFFER,uvbuffer);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1,2,GL_FLOAT,GL_FALSE,0,NULL);//vernum,v_num,type
}
void Buffer::bind_vnbuffer(GLuint vnbuffer){
	glBindBuffer(GL_ARRAY_BUFFER,vnbuffer);
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2,3,GL_FLOAT,GL_FALSE,0,NULL);
}
void Buffer::disable_all_buffer(){
	glDisableVertexAttribArray(0);//vertexbuffer
	glDisableVertexAttribArray(1);//uv
	glDisableVertexAttribArray(2);//vn
	glBindBuffer(GL_ARRAY_BUFFER,0);//unbind buffer
}
