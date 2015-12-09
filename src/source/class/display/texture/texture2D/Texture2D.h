#ifndef TEXTURE2D_H_
#define TEXTURE2D_H_
#include "class/display/texture/Texture.h"
template <class DataType>class Image;
struct drawData2D{
	drawData2D(double _winaspect=1.0,double _texaspect=1.0,GLfloat _alpha=1.0,
			glm::vec3 _pos=glm::vec3(0,0,0),double _size=1.0){
		winaspect=_winaspect;
		texaspect=_texaspect;
		alpha=_alpha;
		pos=_pos;
		size=_size;
	}
	double winaspect;
	double texaspect;
	GLfloat alpha;
	glm::vec3 pos;
	double size;
};
class Texture2D : public Texture {
public:
	Texture2D(GLuint TexID,glm::ivec2 size,GLenum type,GLenum format);
	virtual ~Texture2D();
	static Texture2D* loadBMP(const char * imagepath,int Parameteri=P_MipMap);
	static Texture2D* loadBMP_to_sobel(const char * imagepath,int Parameteri=P_MipMap);
	static Texture2D* gen_texture2D(const void *pixels,glm::ivec2 size,GLint internalformat,GLenum format
			,GLenum type=GL_UNSIGNED_BYTE,int Parameteri=P_MipMap);
	static Texture2D* gen_texture2D(Image<unsigned char>* image,GLint internalformat,
			GLenum type=GL_UNSIGNED_BYTE,int Parameteri=P_MipMap);
	virtual Texture2D* Tex2D();
	virtual int layer()const;
	virtual void draw_texture(Shader* shader2D,double winaspect=1.0,double texaspect=1.0,GLfloat alpha=1.0,
			glm::vec3 pos=glm::vec3(0,0,0),double size=1.0);
	Image<unsigned char>* convert_to_image(GLenum format=GL_RGB);
	glm::ivec2 size;
protected:

};

#endif /* TEXTURE2D_H_ */
