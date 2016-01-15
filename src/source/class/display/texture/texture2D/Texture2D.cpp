#include "class/display/texture/texture2D/Texture2D.h"
#include "class/display/texture/image/Image.h"
#include "class/display/shader/shader2D/Shader2D.h"
#include "class/display/buffer/Buffer.h"
#include "class/tim/math/Math.h"
#include "class/display/uniform/Uniform.h"
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
void Texture2D::draw(Shader* shader2D,DrawData *data){
	DrawData2D *dat=(DrawData2D*)data;
	//shader2D->active_shader();
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_DEPTH_TEST);


    float aspect=Tim::Math::aspect(size)/dat->targetaspect;
    glm::vec2 tsize;
	if(aspect>0.99&&aspect<1.01){
		tsize=glm::vec2(dat->width,dat->width);
	}else{
		tsize=glm::vec2(dat->width,dat->width/aspect);
	}
	GLuint tex_vt=gen_texture_vertex(tsize),tex_uv=gen_texture_uv();

	Buffer::bind_vtbuffer(tex_vt);
	Buffer::bind_uvbuffer(tex_uv);

	sent_uniform(shader2D,0,"Texture");
	glm::vec2 pos=2.0f*(dat->pos)+glm::vec2(tsize.x,-tsize.y)-glm::vec2(1.0,1.0);
	shader2D->sent_Uniform("position",pos);
	shader2D->sent_Uniform("alpha",dat->alpha);

	glDrawArrays(GL_TRIANGLES,0,2*3);


    glDeleteBuffers(1,&tex_vt);
    glDeleteBuffers(1,&tex_uv);
    glDisableVertexAttribArray(0);//vertexbuffer
    glEnable(GL_DEPTH_TEST);
    glDisable(GL_BLEND);
}
Texture2D* Texture2D::loadBMP(const char * imagepath,int Parameteri){
	Image<unsigned char>* bmp_img=new Image<unsigned char>();
	bmp_img->loadBMP(imagepath);
	Texture2D* texture=gen_texture2D(bmp_img,GL_RGB,GL_UNSIGNED_BYTE,Parameteri);//BMP is BGR Format
	delete bmp_img;
	return texture;
}
Image<unsigned char>* Texture2D::convert_to_image(GLenum _format){
	glBindTexture(GL_TEXTURE_2D,TexID);
	Image<unsigned char> *img=new Image<unsigned char>(size,_format);
	glGetTexImage(GL_TEXTURE_2D,0,_format,type,img->data);
	return img;
}
