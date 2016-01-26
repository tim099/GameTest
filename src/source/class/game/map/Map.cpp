#include "class/game/map/Map.h"
#include <cstdio>
#include <ctime>
#include <cstdlib>
#include <iostream>
Map::Map() {
	int mx=MX,my=MY,mz=MZ;
	map=new Tim::Array3D<Cube>(mx,my,mz);
}
Map::~Map() {
	delete map;
}
glm::ivec3 Map::convert_position(glm::vec3 pos){
	return glm::ivec3(floor(pos.x/Map::CUBE_SIZE),floor(pos.y/Map::CUBE_SIZE),floor(pos.z/Map::CUBE_SIZE));
}
void Map::load_map(std::string path){
	FILE * fop = fopen(path.c_str(),"r");
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
					map->get(i,j,k).set(type);
				}else{
					map->get(i,j,k).set(type);
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
	map->get(x,y,z).set(val);
	return true;
}
int Map::get(const int &x,const int &y,const int &z)const{
	if(x<0||x>=MX||y<0||y>=MY||z<0||z>=MZ){
		//std::cout<<"get out of map"<<"x="<<x<<"y="<<y<<"z="<<z<<std::endl;
		return 0;
	}
	return map->get(x,y,z).type;
	//return map->arr[map->size.y*map->size.z*pos.x+map->size.z*pos.y+pos.z].type;//for better performance
}
void Map::tic(){

}
