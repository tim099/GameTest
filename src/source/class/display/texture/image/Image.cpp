#ifndef IMAGE_CPP_
#define IMAGE_CPP_
#include "class/display/texture/image/Image.h"
#include "class/tim/math/Math.h"
#include <cstdio>
#include <cmath>
#include <iostream>
#include <queue>
#include <algorithm>
#include <string>
#include "class/display/texture/image/png/lodepng.h"
#include "class/tim/file/File.h"
namespace Display{
template<class DataType>
Image<DataType>::Image() {
	format = GL_RGB;
	data_size = 3; //3 for RGB
	imageSize = 0;   // = width*height*3
	data = 0;   // Actual RGB data

}
template<class DataType>
Image<DataType>::Image(Image<DataType>* img) {
	format = img->format;
	data_size = img->data_size;   //3 for RGB
	imageSize = img->imageSize;   // = width*height*3
	data = new DataType[imageSize];   // Actual RGB data
	memcpy(data, img->data, imageSize);
}
template<class DataType>
Image<DataType>::Image(glm::ivec2 _size, GLenum _format) {
	initialize(_size, _format);
}
template<class DataType>
Image<DataType>::~Image() {
	if (data)
		delete[] data;
}
template<class DataType>
void Image<DataType>::initialize(glm::ivec2 _size, GLenum _format) {
	format = _format;
	size = _size;
	switch (format) {
	case GL_RGB:
	case GL_BGR:
		data_size = 3;
		break;
	case GL_RGBA:
		data_size = 4;
		break;
	default:
		std::cout << "unknow image format:" << format << std::endl;
	}
	//imageSize=((size.x+(size.x%2))*(size.y)*data_size);
	imageSize = ((size.x) * (size.y) * data_size);
	data = new DataType[imageSize];
}
template<class DataType>
void Image<DataType>::loadImage(const char * imagepath) {
	std::string type = Tim::File::get_type(imagepath);
	if (type == "bmp" || type == "BMP") {
		loadBMP(imagepath);
	} else if (type == "png" || type == "PNG") {
		loadPNG(imagepath);
	} else {
		std::cerr << "unsupport image type:" << type << std::endl;
	}
}
template<class DataType>
void Image<DataType>::loadPNG(const char * imagepath) {
	std::vector<unsigned char> image; //the raw pixels
	unsigned width, height;

	//decode
	unsigned error = lodepng::decode(image, width, height, imagepath);
	if (error) {
		std::cerr << "Image Load png error:" << imagepath << std::endl;
		std::cerr << "error " << error << ": " << lodepng_error_text(error)
				<< std::endl;
	}

	initialize(glm::ivec2(width, height), GL_RGBA);

	memcpy(data, image.data(), sizeof(unsigned char) * image.size());
	flip();
}
template<class DataType>
void Image<DataType>::loadBMP(const char * imagepath) {
	unsigned char header[54]; // Each BMP file begins by a 54-bytes header
	FILE * file = fopen(imagepath, "rb"); // Open the file
	if (!file) {
		printf("Image could not be opened:%s\n", imagepath);
	}
	if (fread(header, 1, 54, file) != 54) { // If not 54 bytes read : problem
		printf("Not a correct BMP file:%s\n", imagepath);
	}
	if (header[0] != 'B' || header[1] != 'M') {
		printf("Not a correct BMP file:%s\n", imagepath);
	}
	initialize(glm::ivec2(*(int*) &(header[0x12]), *(int*) &(header[0x16])),
	GL_BGR);
	fread(data, sizeof(char), imageSize, file);
	fclose(file);

}
template<class DataType>
void Image<DataType>::flip() {
	for (int i = 0; i < (size.y / 2); i++) {
		for (int j = 0; j < size.x; j++) {
			for (int k = 0; k < data_size; k++) {
				std::swap(data[i * size.x * data_size + j * data_size + k],
						data[(size.y - i - 1) * size.x * data_size + j * data_size + k]);
			}
		}
	}
}
template<class DataType>
void Image<DataType>::sub_image3D(GLenum target, int layer, GLenum type) {
	glTexSubImage3D(target, 0, 0, 0, layer, size.x, size.y, 1, format, type,
			data);
}
template<class DataType>
void Image<DataType>::load_sub_image3D(const char *imagepath, GLenum target,
		int layer, GLenum type) {
	Image<DataType>* bmp_img = new Image<DataType>();
	bmp_img->loadBMP(imagepath);
	bmp_img->sub_image3D(target, layer, type);
	delete bmp_img;
}
template<class DataType>
void Image<DataType>::load_sub_image2D(const char *imagepath, GLenum target,
		GLenum internalformat, GLenum format, GLenum type) {
	Image<DataType>* bmp_img = new Image<DataType>();
	bmp_img->loadBMP(imagepath);
	glTexImage2D(target, 0, internalformat, bmp_img->size.x, bmp_img->size.y, 0,
			format, type, bmp_img->data);
	delete bmp_img;
}
}
//template class Image<unsigned char>;
#endif /* IMAGE_CPP_ */
