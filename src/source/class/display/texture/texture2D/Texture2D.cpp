#include "class/display/texture/texture2D/Texture2D.h"
#include "class/display/texture/image/Image.h"
#include "class/display/shader/shader2D/Shader2D.h"
#include "class/display/buffer/Buffer.h"
#include <iostream>
Texture2D::Texture2D(GLuint _TexID,glm::ivec2 _size,GLenum _type,GLenum _format)
: Texture(_TexID,GL_TEXTURE_2D,_type,_format){
	size=_size;
}
Texture2D::~Texture2D() {

}
Texture2D* Texture2D::Tex2D(){
	return this;
}
int Texture2D::layer()const{
	return 0;
}
Texture2D* Texture2D::gen_texture2D(Image<unsigned char>* image,GLint internalformat,
		GLenum type,int Parameteri){
	return gen_texture2D(image->data,image->size,internalformat,image->format,type,Parameteri);
}
Texture2D* Texture2D::gen_texture2D(const void *pixels,glm::ivec2 size,GLint internalformat,GLenum format,GLenum type,int Parameteri){
	GLuint textureID;
	glGenTextures(1,&textureID);
	glBindTexture(GL_TEXTURE_2D,textureID);
	glTexImage2D(GL_TEXTURE_2D,0,internalformat,size.x,size.y,0,format,type,pixels);
	TexFilterParameteri(GL_TEXTURE_2D,Parameteri);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE);//GL_CLAMP
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP_TO_EDGE);
	Texture2D *tex=new Texture2D(textureID,size,type,internalformat);
	return tex;
}
void Texture2D::draw_texture(Shader* shader2D,double winaspect,double texaspect,GLfloat alpha,glm::vec3 pos
		,double size){
	shader2D->active_shader();
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_DEPTH_TEST);

    GLuint tex_vertex=0;
	if(winaspect==texaspect){
		tex_vertex=gen_texture_vertex(1.0,1.0);
	}else{
		float height=1.0;
		double aspect=winaspect/texaspect;
		if(aspect>1.0)height=1.0/aspect;
		tex_vertex=gen_texture_vertex(height,height*aspect);
	}
	Buffer::bind_vtbuffer(tex_vertex);
	sent_uniform(shader2D,0,"myTextureSampler");

	glUniform3f(glGetUniformLocation(shader2D->programID,"position"),pos.x,pos.y,pos.z);
	glUniform1f(glGetUniformLocation(shader2D->programID,"size"),size);
	glUniform1f(glGetUniformLocation(shader2D->programID,"alpha"),alpha);
	glDrawArrays(GL_TRIANGLES,0,2*3);
    glDeleteBuffers(1,&tex_vertex);
    glDisableVertexAttribArray(0);//vertexbuffer
    glEnable(GL_DEPTH_TEST);
    glDisable(GL_BLEND);
}
Texture2D* Texture2D::loadBMP_to_sobel(const char * imagepath,int Parameteri){
	Image<unsigned char>* bmp=new Image<unsigned char>();
	bmp->loadBMP(imagepath);
	Image<unsigned char>::convert_to_sobel(bmp);
	Texture2D* texture=gen_texture2D(bmp,GL_RGB,GL_UNSIGNED_BYTE,Parameteri);//BMP is BGR Format
	return texture;
}
Texture2D* Texture2D::loadBMP(const char * imagepath,int Parameteri){
	Image<unsigned char>* bmp_img=new Image<unsigned char>();
	bmp_img->loadBMP(imagepath);
	Texture2D* texture=gen_texture2D(bmp_img,GL_RGB,GL_UNSIGNED_BYTE,Parameteri);//BMP is BGR Format
	delete bmp_img;
	return texture;
}
void Texture2D::sent_uniform(Shader* shader,int num,const char *name)const{
	shader->sent_Uniform1i(name,num);//texturebuffer
	glActiveTexture(GL_TEXTURE0+num);
	glBindTexture(target,TexID);//GL_TEXTURE_CUBE_MAP
}
Image<unsigned char>* Texture2D::convert_to_image(GLenum _format){
	glBindTexture(GL_TEXTURE_2D,TexID);
	Image<unsigned char> *img=new Image<unsigned char>(size,_format);
	glGetTexImage(GL_TEXTURE_2D,0,_format,type,img->data);
	return img;
}
