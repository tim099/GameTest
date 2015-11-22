#include "class/display/texture/image/ImgData.h"
#include <iostream>
#include <cstdio>
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
template class ImgData<unsigned char>;
