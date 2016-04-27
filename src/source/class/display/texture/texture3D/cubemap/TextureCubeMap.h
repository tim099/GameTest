#ifndef TEXTURECUBEMAP_H_
#define TEXTURECUBEMAP_H_
#include "class/display/texture/Texture.h"
#include <vector>
#include <string>
namespace Display{
class TextureCubeMap : public Texture{
public:
	TextureCubeMap(GLuint _TexID,glm::ivec2 size,GLenum type,GLenum format);
	virtual ~TextureCubeMap();
	virtual int layer()const;
	static TextureCubeMap* gen_CubeMap(glm::ivec2 size,GLint internalformat,GLenum format,
			GLenum type=GL_UNSIGNED_BYTE,int Parameteri=P_Linear);
	static TextureCubeMap* gen_CubeMap(std::vector<std::string>&path,glm::ivec2 size,GLint internalformat,GLenum format,
			GLenum type=GL_UNSIGNED_BYTE,int Parameteri=P_Linear);
	glm::ivec2 size;
};
}
#endif /* TEXTURECUBEMAP_H_ */
