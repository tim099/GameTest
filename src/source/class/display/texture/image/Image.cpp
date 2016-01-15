#ifndef IMAGE_CPP_
#define IMAGE_CPP_
#include "class/display/texture/image/Image.h"
#include "class/tim/math/Math.h"
#include <cstdio>
#include <cmath>
#include <iostream>
#include <queue>

template<class DataType>
Image<DataType>::Image() {
	format=GL_RGB;
	data_size=3;//3 for RGB
	imageSize=0;   // = width*height*3
	data=0;// Actual RGB data

}
template<class DataType>
Image<DataType>::Image(Image<DataType>* img){
	format=img->format;
	data_size=img->data_size;//3 for RGB
	imageSize=img->imageSize;   // = width*height*3
	data=new DataType[imageSize];// Actual RGB data
	memcpy(data,img->data,imageSize);
}
template<class DataType>
Image<DataType>::Image(glm::ivec2 _size,GLenum _format){
	initialize(_size,_format);
}
template<class DataType>
Image<DataType>::~Image() {
	if(data)delete[] data;
}
template<class DataType>
void Image<DataType>::initialize(glm::ivec2 _size,GLenum _format){
	format=_format;
	size=_size;
	switch(format){
		case GL_RGB:
		case GL_BGR:
			data_size=3;
			break;
		case GL_RGBA:
			data_size=4;
			break;
		default:
			std::cout<<"unknow image format:"<<format<<std::endl;
	}
	//imageSize=((size.x+(size.x%2))*(size.y)*data_size);
	imageSize=((size.x)*(size.y)*data_size);
	data=new DataType[imageSize];
}
template<class DataType>
void Image<DataType>::loadImage(const char * imagepath){

}
template<class DataType>
void Image<DataType>::loadBMP(const char * imagepath){
	unsigned char header[54]; // Each BMP file begins by a 54-bytes header
	FILE * file=fopen(imagepath,"rb");// Open the file
	if (!file){printf("Image could not be opened:%s\n",imagepath);}
	if (fread(header,1,54,file)!=54){ // If not 54 bytes read : problem
	    printf("Not a correct BMP file:%s\n",imagepath);
	}
	if (header[0]!='B'||header[1]!='M'){
	    printf("Not a correct BMP file:%s\n",imagepath);
	}
	initialize(glm::vec2(*(int*)&(header[0x12]),*(int*)&(header[0x16])),GL_BGR);
	fread(data,sizeof(char),imageSize,file);
	fclose(file);
}
template<class DataType>
void Image<DataType>::sub_image3D(GLenum target,int layer,GLenum type){
	glTexSubImage3D(target,0,0,0,layer,size.x,size.y,1,format,type,data);
}
template<class DataType>
void Image<DataType>::load_sub_image3D(const char *imagepath,GLenum target,int layer,GLenum type){
	Image<DataType>* bmp_img=new Image<DataType>();
	bmp_img->loadBMP(imagepath);
	bmp_img->sub_image3D(target,layer,type);
	delete bmp_img;
}
template<class DataType>
void Image<DataType>::load_sub_image2D(const char *imagepath,GLenum target,GLenum internalformat,GLenum format,GLenum type){
	Image<DataType>* bmp_img=new Image<DataType>();
	bmp_img->loadBMP(imagepath);
	glTexImage2D(target,0,internalformat,bmp_img->size.x,bmp_img->size.y,0,format,type,bmp_img->data);
	delete bmp_img;
}

//template class Image<unsigned char>;
#endif /* IMAGE_CPP_ */
