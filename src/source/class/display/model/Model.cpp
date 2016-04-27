#include "class/display/model/Model.h"
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <cstring>
#include <algorithm>
#include <cstdio>
#include <iostream>
#include "class/display/model/obj/Obj.h"
#include "class/display/model/obj/Face.h"
#include "class/tim/math/Math.h"
#include "class/display/model/Vertex.h"
#include "class/tim/array/Array.h"
namespace Display{
const GLfloat F_MAX=999999999999999999.0;
const GLfloat F_MIN=-999999999999999999.0;
Model::Model(int _max_len,bool layertex) {
	initial(0,_max_len,layertex);
}
Model::Model(Obj* obj){
	initial(3*obj->fs.size(),3*obj->fs.size());
	Face *f;
	for(unsigned i=0;i<obj->fs.size();i++){
		f=&(obj->fs.at(i));
		for(int j=0;j<3;j++){
			Vertex::fill_vec3(&vtBuffer[9*i+3*j],obj->v.at(f->v[j]));
			Vertex::fill_vec2(&uvBuffer[6*i+2*j],obj->uv.at(f->uv[j]));
			Vertex::fill_vec3(&vnBuffer[9*i+3*j],obj->vn.at(f->n[j]));
		}
		//Vertex::gen_vn(&vtBuffer[9*i],&vnBuffer[9*i]);flat
	}
	check_size();
	//bool Flate=true;
}
void Model::clear(){
	vert_num=0;
}
Model::~Model() {
	delete[] vtBuffer;
	delete[] uvBuffer;
	delete[] vnBuffer;
	if(lyBuffer)delete[] lyBuffer;
}
void Model::initial(int _len,int _max_len,bool layertex){
	vert_num=_len;
	max_vert=_max_len;

	vtBuffer=new GLfloat[3*_max_len];//3 for x,y,z
	uvBuffer=new GLfloat[2*_max_len];//2 for 2D texture UV
	vnBuffer=new GLfloat[3*_max_len];//3 for normal vector x,y,z
	if(layertex){
		lyBuffer=new GLfloat[_max_len];
	}else{
		lyBuffer=0;
	}
}
void Model::max_len_alter(int _len){
	if(_len>max_vert){
		while(_len>max_vert){
			max_vert=2*max_vert+1;
		}

		Tim::Array<GLfloat>::size_alter(vtBuffer,3*vert_num,3*max_vert);
		Tim::Array<GLfloat>::size_alter(uvBuffer,2*vert_num,2*max_vert);
		Tim::Array<GLfloat>::size_alter(vnBuffer,3*vert_num,3*max_vert);
		if(lyBuffer)Tim::Array<GLfloat>::size_alter(lyBuffer,vert_num,max_vert);

		//std::cout<<"model len_alter:"<<max_len<<std::endl;
	}
}
void Model::merge(Model *m,glm::vec3 trans,float layer){
	int prev_len=vert_num;//buffer this before merge!!
	merge(m,trans);
	for(int i=0;i<m->vert_num;i++){
		lyBuffer[prev_len+i]=layer;
	}
}
void Model::merge(Model *m,glm::vec3 trans){
	max_len_alter(vert_num+m->vert_num);
	if(trans!=glm::vec3(0,0,0)){
		for(int i=0;i<m->vert_num;i++){
			vtBuffer[3*(i+vert_num)]=m->vtBuffer[3*i]+trans.x;
			vtBuffer[3*(i+vert_num)+1]=m->vtBuffer[3*i+1]+trans.y;
			vtBuffer[3*(i+vert_num)+2]=m->vtBuffer[3*i+2]+trans.z;
		}
	}else{
		std::copy(m->vtBuffer,m->vtBuffer+3*m->vert_num,vtBuffer+3*vert_num);
	}

	std::copy(m->uvBuffer,m->uvBuffer+2*m->vert_num,uvBuffer+2*vert_num);
	std::copy(m->vnBuffer,m->vnBuffer+3*m->vert_num,vnBuffer+3*vert_num);
	if(m->lyBuffer){
		if(!lyBuffer)std::cerr<<"Model merge failed no layer_buffer!!"<<std::endl;
		else 	     std::copy(m->lyBuffer,m->lyBuffer+m->vert_num,lyBuffer+vert_num);
	}

	vert_num+=m->vert_num;

}
int Model::vtlen()const{
	return 3*vert_num;
}
int Model::uvlen()const{
	return 2*vert_num;
}
int Model::vnlen()const{
	return 3*vert_num;
}
int Model::lylen()const{
	return vert_num;
}
Model* Model::load_obj(const char* path,GLfloat size,bool align_center){
	Obj *obj=Obj::load_obj(path);
	Model* m=new Model(obj);
	delete obj;
	m->scale(size);
	if(align_center)m->translate_to_o();
	return m;
}
void Model::translate_to_o(){
	translate(-mpos);
}
void Model::scale(GLfloat size){
	GLfloat val=size/Tim::Math::max(msize);
	mpos*=val;
	msize*=val;
	for(int i=0;i<vtlen();i++){
		vtBuffer[i]*=val;
	}
}
void Model::check_size(){
	GLfloat x,y,z;
	glm::vec3 max(F_MIN,F_MIN,F_MIN),min(F_MAX,F_MAX,F_MAX);
	for(int i=0;i<vert_num;i++){
		x=vtBuffer[3*i];
		y=vtBuffer[3*i+1];
		z=vtBuffer[3*i+2];
		if(x>max.x)max.x=x;
		if(x<min.x)min.x=x;
		if(y>max.y)max.y=y;
		if(y<min.y)min.y=y;
		if(z>max.z)max.z=z;
		if(z<min.z)min.z=z;
	}
	glm::vec3 size=max-min;
	msize=size;
	mpos=0.5f*(max+min);
	//printf("x=%f,y=%f,z=%f,msize=%f\n",mpos.x,mpos.y,mpos.z,msize);
	//std::cout<<std::endl;
}
int Model::uvdatasize()const{
	return uvlen()*sizeof(GLfloat);
}
int Model::vtdatasize()const{
	return vtlen()*sizeof(GLfloat);
}
int Model::vndatasize()const{
	return vnlen()*sizeof(GLfloat);
}
int Model::lydatasize()const{
	return lylen()*sizeof(GLfloat);
}
void Model::translate(glm::vec3 v){
	for(int i=0;i<vert_num;i++){
		vtBuffer[3*i]+=v.x;
		vtBuffer[3*i+1]+=v.y;
		vtBuffer[3*i+2]+=v.z;
	}
	mpos+=v;
}
}
