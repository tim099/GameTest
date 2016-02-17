#include "class/game/map/cube/CubeEX.h"

CubeEX::CubeEX() {
	type=0;
	x=0,y=0,z=0;
}
CubeEX::~CubeEX() {

}
void CubeEX::draw(){

}
void CubeEX::set_pos(int _x,int _y,int _z){
	x=_x;
	y=_y;
	z=_z;
}
