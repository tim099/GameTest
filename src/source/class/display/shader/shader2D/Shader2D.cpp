#include "class/display/shader/shader2D/Shader2D.h"
#include "class/display/texture/Texture.h"
#include "class/display/buffer/Buffer.h"
Shader2D::Shader2D(std::string _name) : Shader(_name) {
	textureData=0;
}
Shader2D::~Shader2D() {

}
void Shader2D::set_format(GLenum format){
	int textureType=0;
	switch(format){
		case GL_RGB:
			textureType=Type_RGB;
			break;
		case GL_RGBA:
			textureType=Type_RGBA;
			break;
		default:
			textureType=Type_RGB;
	}
	sent_Uniform("textureType",textureType);
}
