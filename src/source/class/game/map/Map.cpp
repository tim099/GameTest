#include "class/game/map/Map.h"
#include <cstdio>
#include <ctime>
#include <cstdlib>
#include <iostream>
Map::Map() {
	for(int i=0;i<MX;i++){
		for(int j=0;j<MY;j++){
			for(int k=0;k<MZ;k++){
				map[i][j][k]=0;
			}
		}
	}
}
Map::~Map() {
	std::cout<<"delete map start"<<std::endl;
	for(int i=0;i<ms.x;i++){
		for(int j=0;j<ms.y;j++){
			for(int k=0;k<ms.z;k++){
				if(map[i][j][k]){
					delete map[i][j][k];
					map[i][j][k]=0;
				}
			}
		}
	}
	std::cout<<"delete map end"<<std::endl;
}
glm::ivec3 Map::convert_position(glm::vec3 pos){
	return glm::ivec3(floor(pos.x/Map::CUBE_SIZE),floor(pos.y/Map::CUBE_SIZE),floor(pos.z/Map::CUBE_SIZE));
}
void Map::load_map(const char *path){
	FILE * fop = fopen(path,"r");
	unsigned seed;
	fscanf(fop,"%d %d %d\n",&ms.x,&ms.y,&ms.z);
	fscanf(fop,"%u\n",&seed);
	if(ms.x>MX||ms.y>MY||ms.z>MZ){
		std::cerr<<"load map error Map size too large"<<std::endl;
		return;
	}
	srand(time(NULL));

	for(int i=0;i<ms.x;i++){
		for(int j=0;j<ms.y;j++){
			for(int k=0;k<ms.z;k++){
				int type=0;
				fscanf(fop,"%d",&type);
				if(type){
					type=rand()%3+1;
					map[i][j][k]=new Cube(type);
				}else{
					map[i][j][k]=new Cube(type);
				}
			}
		}
	}
}
bool Map::set(glm::ivec3 pos,int val){
	if(pos.x<0||pos.x>=MX||pos.y<0||pos.y>=MY||pos.z<0||pos.z>=MZ){
		//std::cout<<"get out of map"<<"x="<<x<<"y="<<y<<"z="<<z<<std::endl;
		return false;
	}
	if(map[pos.x][pos.y][pos.z])map[pos.x][pos.y][pos.z]->type=val;
	return true;
}
int Map::get(glm::ivec3 pos)const{
	if(pos.x<0||pos.x>=MX||pos.y<0||pos.y>=MY||pos.z<0||pos.z>=MZ){
		//std::cout<<"get out of map"<<"x="<<x<<"y="<<y<<"z="<<z<<std::endl;
		return 0;
	}
	if(map[pos.x][pos.y][pos.z]){
		return map[pos.x][pos.y][pos.z]->type;
	}else{
		return 0;
	}
}
void Map::tic(){

}
