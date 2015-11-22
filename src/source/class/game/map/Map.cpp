#include "class/game/map/Map.h"
#include <cstdio>
#include <glm/glm.hpp>
#include <iostream>
Map::Map() {

}
Map::~Map() {

}
void Map::load_map(const char *path){
	FILE * fop = fopen(path,"r");
	glm::ivec3 ms;
	unsigned seed;
	fscanf(fop,"%d %d %d\n",&ms.x,&ms.y,&ms.z);
	fscanf(fop,"%u\n",&seed);
	for(int i=0;i<ms.x;i++){
		for(int j=0;j<ms.y;j++){
			for(int k=0;k<ms.z;k++){
				int type=0;
				fscanf(fop,"%d",&type);
				if(type)map[i][j][k]=true;
				else map[i][j][k]=false;
			}
		}
	}
}
void Map::set(int x,int y,int z,int val){
	map[x][y][z]=val;
}
int Map::get(int x,int y,int z)const{
	return map[x][y][z];
}
