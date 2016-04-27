#include "class/display/model/cube/CubeModel.h"
#include "class/display/model/Vertex.h"
namespace Display{
CubeModel::CubeModel(double size) {
	for(int i=0;i<6;i++)cube[i]=CubeSide(i,size);
}
CubeModel::CubeModel(double sx,double sy,double sz){
	for(int i=0;i<6;i++)cube[i]=CubeSide(i,sx,sy,sz);
}
CubeModel::~CubeModel() {
	for(int i=0;i<6;i++)delete cube[i];
}
Model *CubeModel::CubeSide(int i,double sx,double sy,double sz){
	Model* side=new Model(6);
	Vertex::gen_quad_uv(side->uvBuffer);
	switch(i){
		case 0:
			Vertex::gen_quad_vt(side->vtBuffer,glm::vec3(0,sy,0),glm::vec3(sx,0,sz),true);
			break;
		case 1:
			Vertex::gen_quad_vt(side->vtBuffer,glm::vec3(0,-sy,0),glm::vec3(sx,0,sz),false);
			break;
		case 2:
			Vertex::gen_quad_vt(side->vtBuffer,glm::vec3(sx,0,0),glm::vec3(0,sy,sz),true);
			break;
		case 3:
			Vertex::gen_quad_vt(side->vtBuffer,glm::vec3(-sx,0,0),glm::vec3(0,sy,sz),false);
			break;
		case 4:
			Vertex::gen_quad_vt(side->vtBuffer,glm::vec3(0,0,sz),glm::vec3(sx,sy,0),true);
			break;
		case 5:
			Vertex::gen_quad_vt(side->vtBuffer,glm::vec3(0,0,-sz),glm::vec3(sx,sy,0),false);
			break;
	}
	Vertex::gen_vn(side->vtBuffer,side->vnBuffer);
	Vertex::gen_vn(side->vtBuffer+9,side->vnBuffer+9);
	side->vert_num=6;
	return side;
}
Model *CubeModel::CubeSide(int i,double size){
	Model* side=new Model(6);
	Vertex::gen_quad_uv(side->uvBuffer);
	switch(i){
		case 0:
			Vertex::gen_quad_vt(side->vtBuffer,glm::vec3(0,size,0),glm::vec3(size,0,size),true);
			break;
		case 1:
			Vertex::gen_quad_vt(side->vtBuffer,glm::vec3(0,-size,0),glm::vec3(size,0,size),false);
			break;
		case 2:
			Vertex::gen_quad_vt(side->vtBuffer,glm::vec3(size,0,0),glm::vec3(0,size,size),true);
			break;
		case 3:
			Vertex::gen_quad_vt(side->vtBuffer,glm::vec3(-size,0,0),glm::vec3(0,size,size),false);
			break;
		case 4:
			Vertex::gen_quad_vt(side->vtBuffer,glm::vec3(0,0,size),glm::vec3(size,size,0),true);
			break;
		case 5:
			Vertex::gen_quad_vt(side->vtBuffer,glm::vec3(0,0,-size),glm::vec3(size,size,0),false);
			break;
	}
	Vertex::gen_vn(side->vtBuffer,side->vnBuffer);
	Vertex::gen_vn(side->vtBuffer+9,side->vnBuffer+9);
	side->vert_num=6;
	return side;
}
}

