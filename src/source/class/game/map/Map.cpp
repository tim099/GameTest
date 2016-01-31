#include "class/game/map/Map.h"
#include <cstdio>
#include <ctime>
#include <cstdlib>
#include <iostream>
Map::Map() {
	map=0;
	seed=0;
}
Map::~Map() {
	if(map)delete map;
}
void Map::gen_map(glm::ivec3 _map_size,unsigned _seed){
	map_size=_map_size;
	seed=_seed;
	if(map_size.x>MX||map_size.y>MY||map_size.z>MZ){
		std::cerr<<"Map::gen_map error Map size too large"<<std::endl;
		return;
	}
	if(map)delete map;
	map=new Tim::Array3D<Cube>(map_size.x,map_size.y,map_size.z);
	srand(seed);
	int type;
	for(int i=0;i<map_size.x;i++){
		for(int j=0;j<map_size.y;j++){
			for(int k=0;k<map_size.z;k++){
				type=1;
				if(j<1){//
					map->get(i,j,k).set(type);
				}
			}
		}
	}

}
glm::ivec3 Map::get_size()const{
	return map_size;
}
glm::ivec3 Map::convert_position(glm::vec3 pos){
	return glm::ivec3(floor(pos.x/Map::CUBE_SIZE),floor(pos.y/Map::CUBE_SIZE),floor(pos.z/Map::CUBE_SIZE));
}
void Map::save_map(std::string path){

}
void Map::load_map(std::string path){
	FILE * fop = fopen(path.c_str(),"r");
	fscanf(fop,"%d %d %d\n",&map_size.x,&map_size.y,&map_size.z);
	fscanf(fop,"%u\n",&seed);
	if(map_size.x>MX||map_size.y>MY||map_size.z>MZ){
		std::cerr<<"load map error Map size too large"<<std::endl;
		return;
	}
	srand(time(NULL));
	if(map)delete map;
	map=new Tim::Array3D<Cube>(map_size.x,map_size.y,map_size.z);

	int type;
	for(int i=0;i<map_size.x;i++){
		for(int j=0;j<map_size.y;j++){
			for(int k=0;k<map_size.z;k++){
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
bool Map::set_cube_type(int x,int y,int z,int val){
	if(x<0||x>=map_size.x||y<0||y>=map_size.y||z<0||z>=map_size.z){
		//std::cout<<"get out of map"<<"x="<<x<<"y="<<y<<"z="<<z<<std::endl;
		return false;
	}
	map->get(x,y,z).set(val);
	return true;
}
int Map::get_cube_type(const int &x,const int &y,const int &z)const{
	if(x<0||x>=map_size.x||y<0||y>=map_size.y||z<0||z>=map_size.z){
		//std::cout<<"get out of map"<<"x="<<x<<"y="<<y<<"z="<<z<<std::endl;
		return 0;
	}
	return map->get(x,y,z).type;
	//return map->arr[map->size.y*map->size.z*pos.x+map->size.z*pos.y+pos.z].type;//for better performance
}
void Map::update(){

}
