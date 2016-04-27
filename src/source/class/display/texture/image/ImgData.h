#ifndef IMGDATA_H_
#define IMGDATA_H_
#include <GL/glew.h>
#include <glm/glm.hpp>
namespace Display{
template <class DataType>
class ImgData{
public:
	ImgData();
	~ImgData();

	//DataType *data;// Actual  data
	//GLenum format;
	//glm::ivec2 size;
	//unsigned int imageSize;   // = width*height*3
	//int data_size;
protected:

};
}
#include "class/display/texture/image/ImgData.cpp"
#endif /* IMGDATA_H_ */
