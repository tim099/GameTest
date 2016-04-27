#ifndef IMAGE_H_
#define IMAGE_H_
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <windows.h>
namespace Display{

template <class DataType>class Image;
template <class DataType>
class Image {
public:
	Image();
	Image(Image<DataType>* img);
	Image(glm::ivec2 size,GLenum format=GL_RGB);
	virtual ~Image();
	static void load_sub_image3D(const char * imagepath,
			GLenum target,int layer,GLenum type=GL_UNSIGNED_BYTE);
	static void load_sub_image2D(const char * imagepath,
			GLenum target,GLenum internalformat,GLenum format,GLenum type=GL_UNSIGNED_BYTE);
	void flip();
	void initialize(glm::ivec2 size,GLenum format);
	void loadImage(const char * imagepath);
	void loadBMP(const char * imagepath);
	void loadPNG(const char * imagepath);
	void sub_image3D(GLenum target,int layer,GLenum type=GL_UNSIGNED_BYTE);


	GLenum format;
	glm::ivec2 size;
	unsigned int imageSize;   // = width*height*3
	DataType *data;// Actual RGB data
	int data_size;
protected:


};
}
#include "class/display/texture/image/Image.cpp"
#endif /* IMAGE_H_ */
