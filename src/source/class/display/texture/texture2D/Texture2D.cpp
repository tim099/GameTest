#include "class/display/texture/texture2D/Texture2D.h"
#include "class/display/texture/image/Image.h"
#include "class/display/shader/shader2D/Shader2D.h"
#include "class/display/buffer/Buffer.h"
#include "class/tim/math/Math.h"
#include "class/display/uniform/Uniform.h"
#include "class/tim/file/File.h"
#include "class/display/window/ViewPort.h"
#include <iostream>
namespace Display{
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
double Texture2D::get_aspect(){
	return Tim::Math::aspect(size);
}
Texture2D* Texture2D::gen_texture2D(Image<unsigned char>* image,GLint internalformat,
		GLenum type,int Parameteri){
	return gen_texture2D(image->data,image->size,internalformat,image->format,type,Parameteri);
}
Texture2D* Texture2D::gen_texture2D(unsigned char *pixels,glm::ivec2 size,GLint internalformat,GLenum format,GLenum type,int Parameteri){
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
void Texture2D::draw(Shader2D* shader2D,DrawData *data){
	DrawData2D *dat=(DrawData2D*)data;
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_DEPTH_TEST);

	float targetaspect=ViewPort::get_cur_viewport_aspect();

    glm::vec2 tsize;
    float aspect=Tim::Math::aspect(size)/targetaspect;
    tsize=Tim::Math::get_size(dat->width,aspect);
    if(!dat->height==DrawData2D::AutoHeight){
    	tsize.y*=dat->height;
    }

	GLuint tex_vt=gen_texture_vertex(tsize),tex_uv=gen_texture_uv();

	Buffer::bind_vtbuffer(tex_vt);
	Buffer::bind_uvbuffer(tex_uv);

	sent_uniform(shader2D,0,"Texture");
	math::vec2<float> pos=(dat->pos)*2.0f+
			math::vec2<float>(tsize.x,-tsize.y)-
			math::vec2<float>(1.0,1.0);
	shader2D->sent_Uniform("position",pos);
	shader2D->sent_Uniform("alpha",dat->alpha);

	glDrawArrays(GL_TRIANGLES,0,2*3);


    glDeleteBuffers(1,&tex_vt);
    glDeleteBuffers(1,&tex_uv);

    glEnable(GL_DEPTH_TEST);
    glDisable(GL_BLEND);
}
Texture2D* Texture2D::loadImage(const char * imagepath,int Parameteri){
	std::string type=Tim::File::get_type(imagepath);;
	if (type == "bmp" || type == "BMP") {
		return loadBMP(imagepath,Parameteri);
	} else if (type == "png" || type == "PNG") {
		return loadPNG(imagepath,Parameteri);
	} else {
		std::cerr << "unsupport image type:" << type << std::endl;
	}
	return 0;
}
Texture2D* Texture2D::loadPNG(const char * imagepath,int Parameteri){
	Image<unsigned char>* img=new Image<unsigned char>();
	img->loadPNG(imagepath);
	Texture2D* texture=gen_texture2D(img,GL_RGBA,GL_UNSIGNED_BYTE,Parameteri);//BMP is BGR Format
	delete img;
	return texture;
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
}
