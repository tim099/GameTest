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
bool Map::set(int x,int y,int z,int val){
	if(x<0||x>=MX||y<0||y>=MY||z<0||z>=MZ){
		//std::cout<<"get out of map"<<"x="<<x<<"y="<<y<<"z="<<z<<std::endl;
		return false;
	}
	if(map[x][y][z])map[x][y][z]->type=val;
	return true;
}
int Map::get(int x,int y,int z)const{
	if(x<0||x>=MX||y<0||y>=MY||z<0||z>=MZ){
		//std::cout<<"get out of map"<<"x="<<x<<"y="<<y<<"z="<<z<<std::endl;
		return 0;
	}
	if(map[x][y][z]){
		return map[x][y][z]->type;
	}else{
		return 0;
	}
}
void Map::tic(){

}
