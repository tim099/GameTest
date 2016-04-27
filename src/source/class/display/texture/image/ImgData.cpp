#ifndef IMGDATA_CPP_
#define IMGDATA_CPP_
#include "class/display/texture/image/ImgData.h"
#include <iostream>
#include <cstdio>
namespace Display{
template <class DataType>
ImgData<DataType>::ImgData() {
	//format=GL_RGB;
	//data_size=3;//3 for RGB
	//imageSize=0;   // = width*height*3
	//data=0;// Actual RGB data
}
template <class DataType>
ImgData<DataType>::~ImgData() {

}
}
#endif /* IMGDATA_H_ */
