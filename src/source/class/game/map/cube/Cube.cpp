#include "class/game/map/cube/Cube.h"

Cube::Cube(unsigned char _type) {
	type=_type;
	cubeEX=0;
}
Cube::Cube(){
	type=0;
	cubeEX=0;
}
Cube::~Cube() {

}
void Cube::set(CubeEX *_cubeEX){
	cubeEX=_cubeEX;
	type=-1;
}
void Cube::set(unsigned char _type){
	cubeEX=0;
	type=_type;
}
