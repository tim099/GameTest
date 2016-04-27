#include "class/display/model/Vertex.h"
#include <iostream>
namespace Display{
Vertex::Vertex() {

}
Vertex::~Vertex() {

}
void Vertex::fill_vec3(GLfloat* vt,glm::vec3 v,int num){
	for(int i=0;i<num;i++){
		vt[3*i]=v.x;vt[3*i+1]=v.y;vt[3*i+2]=v.z;
	}
}
void Vertex::fill_vec2(GLfloat* vt,glm::vec2 v,int num){
	for(int i=0;i<num;i++){
		vt[2*i]=v.x;vt[2*i+1]=v.y;
	}
}
void Vertex::gen_vn(GLfloat* vt,GLfloat* vn){
	glm::vec3 p1(vt[0],vt[1],vt[2]),p2(vt[3],vt[4],vt[5]),p3(vt[6],vt[7],vt[8]);
	glm::vec3 n=glm::normalize(glm::cross(p1-p2,p1-p3));
	for(int i=0;i<3;i++){
		vn[3*i]=n.x;
		vn[3*i+1]=n.y;
		vn[3*i+2]=n.z;
	}
}
void Vertex::gen_quad_uv(GLfloat* uvBuffer,glm::vec2 a,glm::vec2 b){
	fill_vec2(uvBuffer,glm::vec2(b.x,b.y));
	fill_vec2(uvBuffer+2,glm::vec2(a.x,b.y));
	fill_vec2(uvBuffer+4,glm::vec2(b.x,a.y));

	fill_vec2(uvBuffer+6,glm::vec2(b.x,a.y));
	fill_vec2(uvBuffer+8,glm::vec2(a.x,b.y));
	fill_vec2(uvBuffer+10,glm::vec2(a.x,a.y));
}
void Vertex::gen_quad_vt(GLfloat* vtBuffer,glm::vec3 p,glm::vec3 size,bool up){
	glm::vec3 d1,d2,d3,d4;
	if(size.z==0){
		if(up){
			d1=glm::vec3(size.x,size.y,0);
			d2=glm::vec3(-size.x,size.y,0);
			d3=glm::vec3(size.x,-size.y,0);
			d4=glm::vec3(-size.x,-size.y,0);
		}else{
			d1=glm::vec3(-size.x,size.y,0);
			d2=glm::vec3(size.x,size.y,0);
			d3=glm::vec3(-size.x,-size.y,0);
			d4=glm::vec3(size.x,-size.y,0);
		}
	}else if(size.y==0){
		if(up){
			d1=glm::vec3(-size.x,0,size.z);
			d2=glm::vec3(size.x,0,size.z);
			d3=glm::vec3(-size.x,0,-size.z);
			d4=glm::vec3(size.x,0,-size.z);
		}else{
			d1=glm::vec3(size.x,0,size.z);
			d2=glm::vec3(-size.x,0,size.z);
			d3=glm::vec3(size.x,0,-size.z);
			d4=glm::vec3(-size.x,0,-size.z);
		}
	}else if(size.x==0){
		if(up){
			d1=glm::vec3(0,size.y,-size.z);
			d2=glm::vec3(0,size.y,size.z);
			d3=glm::vec3(0,-size.y,-size.z);
			d4=glm::vec3(0,-size.y,size.z);
		}else{
			d1=glm::vec3(0,size.y,size.z);
			d2=glm::vec3(0,size.y,-size.z);
			d3=glm::vec3(0,-size.y,size.z);
			d4=glm::vec3(0,-size.y,-size.z);
		}

	}

	fill_vec3(vtBuffer,p+d1);
	fill_vec3(vtBuffer+3,p+d2);
	fill_vec3(vtBuffer+6,p+d3);
	fill_vec3(vtBuffer+9,p+d3);
	fill_vec3(vtBuffer+12,p+d2);
	fill_vec3(vtBuffer+15,p+d4);
}
}
