#include "class/display/texture/texture3D/cubemap/TextureCubeMap.h"
namespace Display{
TextureCubeMap::TextureCubeMap(GLuint _TexID,glm::ivec2 _size,GLenum _type,GLenum _format)
: Texture(_TexID,GL_TEXTURE_CUBE_MAP,_type,_format){
	size=_size;
}
TextureCubeMap::~TextureCubeMap() {

}
TextureCubeMap* TextureCubeMap::gen_CubeMap(glm::ivec2 size,GLint internalformat,GLenum format,GLenum type,int Parameteri){
	GLuint texture;
	glGenTextures(1,&texture);
	glBindTexture(GL_TEXTURE_CUBE_MAP,texture);
	glTexImage3D(GL_TEXTURE_CUBE_MAP,0,internalformat,size.x,size.y,6,0,format,type,NULL);//0=level,0=border

	glTexParameteri(GL_TEXTURE_CUBE_MAP,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP,GL_TEXTURE_WRAP_T,GL_CLAMP_TO_EDGE);
	TexFilterParameteri(GL_TEXTURE_CUBE_MAP,Parameteri);
	for (int i=0;i<6;i++) {
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X+i,0,internalformat,size.x,size.y,0,format,type,0);
	}
	glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);
	TextureCubeMap *tex=new TextureCubeMap(texture,size,type,format);
	return tex;
}
TextureCubeMap* TextureCubeMap::gen_CubeMap(std::vector<std::string>&path,glm::ivec2 size,GLint internalformat,GLenum format,
		GLenum type,int Parameteri){
	TextureCubeMap *tex=gen_CubeMap(size,internalformat,format,type,Parameteri);
	for(unsigned i=0;i<6;i++){
		Image<unsigned char>::load_sub_image2D(path.at(i).c_str(),GL_TEXTURE_CUBE_MAP_POSITIVE_X+i,
				internalformat,format,type);
	}
	TexFilterParameteri(GL_TEXTURE_CUBE_MAP,Parameteri);

	return tex;
}

int TextureCubeMap::layer()const{
	return 6;
}
}
