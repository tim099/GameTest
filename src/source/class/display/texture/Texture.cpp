#include "class/display/texture/Texture.h"
#include "class/tim/string/String.h"
#include "class/display/texture/texture2D/Texture2D.h"
#include "class/display/buffer/Buffer.h"
#include "class/display/model/Vertex.h"
#include "class/display/shader/shader2D/Shader2D.h"
#include <cstdio>
#include <iostream>
#include <cmath>
#include <cstring>
#include <GL/glfw3.h>
Texture::Texture(GLuint _TexID,GLenum _target,GLenum _type,GLenum _format) {
	TexID=_TexID;
	target=_target;
	type=_type;
	format=_format;
}
Texture::~Texture() {
	glDeleteTextures(1,&TexID);
}
Texture2D* Texture::Tex2D(){
	return 0;
}
void Texture::bind_texture(){
	glBindTexture(target,TexID);
}
void Texture::sent_uniform(Shader* shader,int num,const char *name)const{
	std::cerr<<"please implement texture sent_uniform function"<<std::endl;
}
void Texture::TexFilterParameteri(GLenum target,int Parameteri){
	switch(Parameteri){
		case P_NONE:
			break;
		case P_MipMap:
			glTexParameteri(target,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
			glTexParameteri(target,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_LINEAR);
			glTexParameteri(target,GL_TEXTURE_BASE_LEVEL,0);
			glTexParameteri(target,GL_TEXTURE_MAX_LEVEL,20);
			glGenerateMipmap(target);
			break;
		case P_Linear:
			glTexParameteri(target,GL_TEXTURE_MAG_FILTER,GL_LINEAR);//GL_NEAREST
			glTexParameteri(target,GL_TEXTURE_MIN_FILTER,GL_LINEAR);//GL_NEAREST
			break;
		case P_Nearest:
			glTexParameteri(target,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
			glTexParameteri(target,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
			break;
		default:
			std::cout<<"err unknow texture Parameteri type:"<<Parameteri<<std::endl;

	}
}
void Texture::usetextureVec(Shader* shader,std::vector<Texture*>& texvec,int num,const char *name){
	int slen=strlen(name);
	char temp[100];
	for(int i=0;i<slen;i++){
		temp[i]=name[i];
	}
	for(unsigned i=0;i<texvec.size();i++){
		Tim::String::gen_array_num(temp+slen,i);
		//sprintf(temp,"%s[%d]",name,num);
		texvec.at(i)->sent_uniform(shader,i+num,temp);
	}
}
GLuint Texture::gen_texture_vertex(GLfloat width,GLfloat height,glm::vec3 pos){
	GLfloat vertex_buffer_data[18];
	Vertex::gen_quad_vt(vertex_buffer_data,pos,glm::vec3(width,height,0),true);
	return Buffer::gen_buffer(vertex_buffer_data,sizeof(vertex_buffer_data));
}
int Texture::layer()const{
	return 0;
}
void Texture::draw_texture(Shader* shader2D,double winaspect,double texaspect,GLfloat alpha,glm::vec3 pos
		,double size){
	std::cerr<<"error not implement draw texture in this class"<<std::endl;
}