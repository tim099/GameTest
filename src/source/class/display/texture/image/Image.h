#ifndef IMAGE_H_
#define IMAGE_H_
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <windows.h>

template <class DataType>class Image;

template <class DataType>
struct Sobeldata{
	Sobeldata(Image<DataType>* image,glm::vec2 dv,glm::ivec2 se,float clip)
		:image(image),dv(dv),se(se),clip(clip){
		done=false;
	}
	virtual ~Sobeldata(){

	}
	Image<DataType>*image;
	glm::vec2 dv;
	glm::ivec2 se;
	bool done;
	float clip;
};
template <class DataType>
class Image {
public:
	Image();
	Image(Image<DataType>* img);
	Image(glm::ivec2 size,GLenum format=GL_RGB);
	virtual ~Image();
	static void convert_to_sobel(Image<DataType>* image,
			glm::vec2 dv=glm::vec2(2,1),float clip=0.0);
	static void load_sub_image(const char * imagepath,
			GLenum target,int layer,GLenum type=GL_UNSIGNED_BYTE);

	void initialize(glm::ivec2 size,GLenum format);
	void loadBMP(const char * imagepath);
	void sub_image(GLenum target,int layer,GLenum type=GL_UNSIGNED_BYTE);

	GLenum format;
	glm::ivec2 size;
	unsigned int imageSize;   // = width*height*3
	DataType *data;// Actual RGB data
	int data_size;
protected:
	static int sobel(unsigned char arr[3][3],glm::vec2 dv);
	static DWORD WINAPI parallize_sobel(LPVOID lpParameter);

};

#endif /* IMAGE_H_ */
