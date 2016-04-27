#include "class/display/model/obj/Face.h"
namespace Display{
Face::Face(int _v[3],int _uv[3],int _n[3]) {
	for(int i=0;i<3;i++){
		v[i]=_v[i]-1;
		uv[i]=_uv[i]-1;
		n[i]=_n[i]-1;
	}
}
Face::~Face() {

}
}
