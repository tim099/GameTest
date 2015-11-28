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
	data=new unsigned char [imageSize];
}
template<class DataType>
void Image<DataType>::loadBMP(const char * imagepath){
	unsigned char header[54]; // Each BMP file begins by a 54-bytes header
	FILE * file = fopen(imagepath,"rb");// Open the file
	if (!file){printf("Image could not be opened:%s\n",imagepath);}
	if (fread(header,1,54,file)!=54){ // If not 54 bytes read : problem
	    printf("Not a correct BMP file:%s\n",imagepath);
	}
	if (header[0]!='B'||header[1]!='M'){
	    printf("Not a correct BMP file:%s\n",imagepath);
	}
	initialize(glm::vec2(*(int*)&(header[0x12]),*(int*)&(header[0x16])),GL_BGR);
	fread(data,sizeof(char),imageSize,file);
	format=GL_BGR;
	fclose(file);
}
template<class DataType>
void Image<DataType>::sub_image(GLenum target,int layer,GLenum type){
	glTexSubImage3D(target,0,0,0,layer,size.x,size.y,1,format,type,data);
}
template<class DataType>
void Image<DataType>::load_sub_image(const char *imagepath,GLenum target,int layer,GLenum type){
	Image<DataType>* bmp_img=new Image<DataType>();
	bmp_img->loadBMP(imagepath);
	bmp_img->sub_image(target,layer,type);
	delete bmp_img;
}
template<class DataType>
void Image<DataType>::convert_to_sobel(Image<DataType>* image,glm::vec2 dv,float clip){
	int col;
	for(unsigned i=0;i<image->imageSize/3;i++){// convert to grey
		col=(((int)image->data[3*i]+(int)image->data[3*i+1]+(int)image->data[3*i+2])/3);
		image->data[3*i]=(unsigned char)col;
		//if(i%50000==0)std::cout<<col<<std::endl;
	}
	//std::cout<<image->size.x<<","<<image->size.y<<"total="<<image->imageSize<<std::endl;
	std::queue<Sobeldata<DataType>*>sobel_q;
	glm::ivec2 se;
	int seg=30;
	for (int i=0;seg*i<=image->size.y;i++){
		se.x=i*seg;
		se.y=(i+1)*seg;
		if(se.y>image->size.y)se.y=image->size.y;
		Sobeldata<DataType>* dat=new Sobeldata<DataType>(image,dv,se,clip);
		CreateThread(NULL,0,parallize_sobel,dat,0,0);
		//parallize_sobel(dat);
		sobel_q.push(dat);
	}
	while(!sobel_q.empty()){
		if(sobel_q.front()->done){
			delete sobel_q.front();
			sobel_q.pop();
		}
	}
	for(unsigned i=0;i<image->imageSize/3;i++){//convert to BMP
		image->data[3*i]=image->data[3*i+2];
		image->data[3*i+1]=image->data[3*i+2];
	}

}
template<class DataType>
int Image<DataType>::sobel(unsigned char arr[3][3],glm::vec2 dv){
	int GX=-dv.y*arr[0][0]+dv.y*arr[0][2]-dv.x*arr[1][0]
	   +dv.x*arr[1][2]-dv.y*arr[2][0]+dv.y*arr[2][2];
	int GY=-dv.y*arr[0][0]+dv.y*arr[2][0]-dv.x*arr[0][1]
	   +dv.x*arr[2][1]-dv.y*arr[0][2]+dv.y*arr[2][2];
	return sqrt(GX*GX+GY*GY);
}
template<class DataType>
DWORD WINAPI Image<DataType>::parallize_sobel(LPVOID lpParameter){
	Sobeldata<DataType>* dat=(Sobeldata<DataType>*)lpParameter;
	int value;
	int GX,GY;
	int x,y;
	unsigned char arr[3][3];
	for(int i=dat->se.x;i<dat->se.y;i++){
		for(int j=0;j<dat->image->size.x;j++){
			for(int l=0;l<3;l++){
				for(int m=0;m<3;m++){
					x=j+m-1,y=i+l-1;
					if(x<0)x=0;
					if(y<0)y=0;
					if(x>=(int)dat->image->size.x)x=dat->image->size.x-1;
					if(y>=(int)dat->image->size.y)y=dat->image->size.y-1;
					arr[l][m]=dat->image->data[(x+y*(dat->image->size.x))*3];
				}
			}
			GX=-dat->dv.y*arr[0][0]+dat->dv.y*arr[0][2]-dat->dv.x*arr[1][0]
			   +dat->dv.x*arr[1][2]-dat->dv.y*arr[2][0]+dat->dv.y*arr[2][2];
			GY=-dat->dv.y*arr[0][0]+dat->dv.y*arr[2][0]-dat->dv.x*arr[0][1]
			   +dat->dv.x*arr[2][1]-dat->dv.y*arr[0][2]+dat->dv.y*arr[2][2];
			value=sqrt(GX*GX+GY*GY);
			//value=sobel(arr,dat->dv);

			value=(value<255?value:255);
			if(dat->clip!=0.0f){
				if((float)value>255.0f*dat->clip){
					value=255;
				}else{
					value=0;
				}
			}
			dat->image->data[3*(j+i*(dat->image->size.x))+2]=(unsigned char)value;
		}
	}
	dat->done=true;
	return 0;
}
template class Image<unsigned char>;
