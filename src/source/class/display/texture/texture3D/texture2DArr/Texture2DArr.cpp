#include "class/display/texture/texture3D/Texture2DArr/Texture2DArr.h"
#include "class/display/texture/image/Image.h"
#include "class/display/shader/shader2D/Shader2D.h"
#include "class/display/buffer/Buffer.h"
namespace Display{
Texture2DArr::Texture2DArr(GLuint _TexID,glm::ivec3 _size,GLenum _type,GLenum _format)
: Texture(_TexID,GL_TEXTURE_2D_ARRAY,_type,_format){
	size=_size;
}
Texture2DArr::~Texture2DArr() {

}
void Texture2DArr::draw_texture(Shader* shader2D,double winaspect,double texaspect,GLfloat alpha,glm::vec3 pos
		,double size){

}
int Texture2DArr::layer()const{
	return size.z;
}
Texture2DArr* Texture2DArr::gen_texture2DArr(std::vector<std::string>&path,glm::ivec3 size,GLint internalformat,GLenum format,
		GLenum type,int Parameteri){
	Texture2DArr* texarr=Texture2DArr::gen_texture2DArr(size,internalformat,format,type,P_NONE);
	for(unsigned i=0;i<path.size();i++){
		Image<unsigned char>::load_sub_image3D(path.at(i).c_str(),texarr->target,i,type);
	}
	TexFilterParameteri(GL_TEXTURE_2D_ARRAY,Parameteri);
	return texarr;
}
Texture2DArr* Texture2DArr::gen_texture2DArr(glm::ivec3 size,GLint internalformat,GLenum format,
		GLenum type,int Parameteri){
	GLuint texture;
	glGenTextures(1,&texture);
	glBindTexture(GL_TEXTURE_2D_ARRAY,texture);
	glTexImage3D(GL_TEXTURE_2D_ARRAY,0,internalformat,size.x,size.y,size.z,0,format,type,NULL);//0=level,0=border

	glTexParameteri(GL_TEXTURE_2D_ARRAY,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D_ARRAY,GL_TEXTURE_WRAP_T,GL_CLAMP_TO_EDGE);
	TexFilterParameteri(GL_TEXTURE_2D_ARRAY,Parameteri);

	Texture2DArr *tex=new Texture2DArr(texture,size,type,format);

	return tex;
}
}
