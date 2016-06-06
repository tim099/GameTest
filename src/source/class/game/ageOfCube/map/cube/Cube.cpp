#include "class/game/ageOfCube/map/cube/Cube.h"

//#include "class/game/ageOfCube/map/cube/CubeEX.h"
#include <iostream>
namespace AOC{
bool Cube::cube_inited=false;
unsigned char Cube::cube_end=0;
unsigned char Cube::stone=0;
unsigned char Cube::dirt=0;
unsigned char Cube::sand=0;
unsigned char Cube::grass=0;
unsigned char Cube::coal=0;
std::vector<unsigned char>Cube::basic_cubes;
void Cube::Cube_init(){
	if(cube_inited)return;
	unsigned char type_num=cube_start;

	stone=type_num++;
	dirt=type_num++;
	sand=type_num++;
	grass=type_num++;
	coal=type_num++;

	cube_end=type_num-1;
	create_basic_cubes();
	//for(unsigned i=0;i<basic_cubes.size();i++){
		//std::cout<<"cube="<<(int)basic_cubes.at(i)<<std::endl;
	//}


	cube_inited=true;
}
void Cube::create_basic_cubes(){
	basic_cubes.push_back(Cube::stone);
	basic_cubes.push_back(Cube::dirt);
	basic_cubes.push_back(Cube::sand);
}
Cube::Cube(){

}
Cube::~Cube() {

}
void Cube::update(int x,int y,int z,int ux,int uy,int uz){

}
}
