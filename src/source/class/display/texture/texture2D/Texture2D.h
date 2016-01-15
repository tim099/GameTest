#ifndef TEXTURE2D_H_
#define TEXTURE2D_H_
#include "class/display/texture/Texture.h"
#include "class/display/texture/texture2D/DrawData2D.h"

template <class DataType>class Image;

class Texture2D : public Texture {
public:
	Texture2D(GLuint TexID,glm::ivec2 size,GLenum type,GLenum format);
	virtual ~Texture2D();
	static Texture2D* loadBMP(const char * imagepath,int Parameteri=P_MipMap);
	static Texture2D* gen_texture2D(const void *pixels,glm::ivec2 size,GLint internalformat,GLenum format
			,GLenum type=GL_UNSIGNED_BYTE,int Parameteri=P_MipMap);
	static Texture2D* gen_texture2D(Image<unsigned char>* image,GLint internalformat,
			GLenum type=GL_UNSIGNED_BYTE,int Parameteri=P_MipMap);
	virtual Texture2D* Tex2D();
	virtual int layer()const;

	Image<unsigned char>* convert_to_image(GLenum format=GL_RGB);
	glm::ivec2 size;
protected:
	virtual void draw(Shader* shader2D,DrawData *data);
};

#endif /* TEXTURE2D_H_ */
