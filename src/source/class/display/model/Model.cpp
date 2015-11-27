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
const GLfloat F_MAX=999999999999999999.0;
const GLfloat F_MIN=-999999999999999999.0;
Model::Model(int _max_len) {
	initial(0,_max_len);
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
	len=0;
	mat=glm::vec4(0.3,0.4,0.01,0.05);
}
Model::~Model() {
	delete[] vtBuffer;
	delete[] uvBuffer;
	delete[] vnBuffer;
}
void Model::initial(int _len,int _max_len){
	len=_len;
	max_len=_max_len;

	vtBuffer=new GLfloat[3*_max_len];//3 for each point
	uvBuffer=new GLfloat[2*_max_len];
	vnBuffer=new GLfloat[3*_max_len];

	mat=glm::vec4(0.3,0.4,0.01,0.05);
}
void Model::len_alter(int _len){
	if(_len>max_len){
		while(_len>max_len)max_len*=2;
		GLfloat* tmp_vtBuffer=new GLfloat[3*max_len];
		GLfloat* tmp_uvBuffer=new GLfloat[2*max_len];
		GLfloat* tmp_vnBuffer=new GLfloat[3*max_len];
		std::copy(vtBuffer,vtBuffer+3*len,tmp_vtBuffer);
		std::copy(uvBuffer,uvBuffer+2*len,tmp_uvBuffer);
		std::copy(vnBuffer,vnBuffer+3*len,tmp_vnBuffer);
		std::swap(vtBuffer,tmp_vtBuffer);
		std::swap(uvBuffer,tmp_uvBuffer);
		std::swap(vnBuffer,tmp_vnBuffer);
		delete tmp_vtBuffer;
		delete tmp_uvBuffer;
		delete tmp_vnBuffer;
		//std::cout<<"model len_alter:"<<max_len<<std::endl;
	}
}
void Model::merge(Model *m,glm::vec3 trans){
	len_alter(len+m->len);
	//std::copy(m->vtBuffer,m->vtBuffer+3*m->len,tmp_vtBuffer+3*len);
	for(int i=0;i<m->len;i++){
		vtBuffer[3*(i+len)]=m->vtBuffer[3*i]+trans.x;
		vtBuffer[3*(i+len)+1]=m->vtBuffer[3*i+1]+trans.y;
		vtBuffer[3*(i+len)+2]=m->vtBuffer[3*i+2]+trans.z;
	}
	std::copy(m->uvBuffer,m->uvBuffer+2*m->len,uvBuffer+2*len);
	std::copy(m->vnBuffer,m->vnBuffer+3*m->len,vnBuffer+3*len);

	len+=m->len;
}
int Model::vtlen()const{
	return 3*len;
}
int Model::uvlen()const{
	return 2*len;
}
int Model::vnlen()const{
	return 3*len;
}
Model* Model::load_obj(const char* path,GLfloat size,bool translate_to_o){
	Obj *obj=Obj::load_obj(path);
	Model* m=new Model(obj);
	delete obj;
	m->scale(size);
	if(translate_to_o)m->translate_to_o();
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
	for(int i=0;i<(vtlen()/3);i++){
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
void Model::translate(glm::vec3 v){
	for(int i=0;i<(vtlen()/3);i++){
		vtBuffer[3*i]+=v.x;
		vtBuffer[3*i+1]+=v.y;
		vtBuffer[3*i+2]+=v.z;
	}
	mpos+=v;
}
