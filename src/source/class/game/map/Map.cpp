#include "class/game/map/Map.h"
#include <cstdio>
#include <ctime>
#include <cstdlib>
#include <iostream>

Map::Map() {
	map=0;
	seed=0;
	times=0;
	ground_height=150;
	Cube::Cube_init();
}
Map::~Map() {
	if(map)delete map;
}
void Map::gen_stone(unsigned char &type,const double &x,const double &y,const double &z){
	double type_val=noise.noise(x,y,z,0.1);
	if((type_val<0.3)){
		type=Cube::coal;
	}
}
void Map::gen_dirt(unsigned char &type,const int &i,const int &j,const int &k){
	if(get_cube_type(i,j+1,k)==0||get_cube_type(i+1,j,k)==0||
			get_cube_type(i-1,j,k)==0||get_cube_type(i,j,k+1)==0||
			get_cube_type(i,j,k-1)==0){//&&(type_val>0.3)
		type=Cube::grass;
	}
}
void Map::gen_cube_type(int i,int j,int k,
		const double &stone_height,
		const double &height,const double &wetness){
	unsigned char type;
	double x=((double)i/map_size.x);
	double y=((double)j/map_size.y);
	double z=((double)k/map_size.z);

	if(j<stone_height*ground_height){
		type=Cube::stone;
	}else{
		if(wetness<0.45&&
				y>stone_height+0.05*wetness){//0.1*type_val+
			type=Cube::sand;
		}else{
			type=Cube::dirt;
		}

	}

	if(type==Cube::dirt){
		gen_dirt(type,i,j,k);//generate type derive from dirt(dirt,grass.. etc
	}else if(type==Cube::stone){
		gen_stone(type,x,y,z);//generate type derive from stone(coal,iron..etc
	}else if(type==Cube::sand){

	}
	map->get(i,j,k).set(type);
}
void Map::gen_map_shape(){
	double height;
	for (int i = 0; i < map_size.x; i++) {
		for (int k = 0; k < map_size.z; k++) {
			height=get_height(i,k);
			for (int j = 0; j < map_size.y; j++) {
				if (j < ground_height * height) {
					map->get(i, j, k).set(1);
				}
			}
		}
	}
}
void Map::regen_map(){
	double stone_height;
	double height;
	double wetness;
	gen_map_shape();
	for(int i=0;i<map_size.x;i++){
		for(int k=0;k<map_size.z;k++){
			height=get_height(i,k);
			stone_height=height*noise.noise(((double)i/map_size.x),
					0,((double)k/map_size.z),0.01);
			wetness=get_wetness(i,k,height);

			for(int j=0;j<map_size.y;j++){
				if(map->get(i,j,k).type!=0){
					gen_cube_type(i,j,k,stone_height,height,wetness);
				}
			}
		}
	}
	times++;
}
void Map::gen_map(glm::ivec3 _map_size,unsigned _seed,int _ground_height){
	map_size=_map_size;
	ground_height=_ground_height;
	if(ground_height>map_size.y){
		ground_height=map_size.y;
	}
	seed=_seed;
	if(map_size.x>MX||map_size.y>MY||map_size.z>MZ){
		std::cerr<<"Map::gen_map error Map size too large"<<std::endl;
		return;
	}
	if(map)delete map;
	map=new Tim::Array3D<Cube>(map_size.x,map_size.y,map_size.z);
	noise.init(seed);
	//srand(seed);

	regen_map();

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
		return -1;
	}
	return map->get(x,y,z).type;
	//return map->arr[map->size.y*map->size.z*pos.x+map->size.z*pos.y+pos.z].type;//for better performance
}
void Map::update(){

}
