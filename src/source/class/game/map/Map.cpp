
#include "class/game/map/Map.h"
#include "class/game/map/MapSeg.h"
#include "class/game/map/DisplayMap.h"

#include "class/game/map/cube/Cube.h"
#include "class/game/map/cube/CubeEX.h"
#include "class/game/map/cube/CubeOutOfEdge.h"
#include "class/game/map/cube/CubeNull.h"

#include "class/game/map/cube/AllCubes.h"
#include "class/game/map/landscape/LandscapeCreator.h"
#include "class/game/map/cube/water/Water.h"

#include <cstdio>
#include <ctime>
#include <cstdlib>
#include <iostream>
#include <algorithm>
Map::Map() {
	dp_map=0;
	map=0;
	map_segs=0;
	seed=0;
	times=0;
	ground_height=150;
	cube_out_of_edge=new CubeOutOfEdge();
	cube_null=new CubeNull();
	cube_water=new Water();
	all_cubes=new AllCubes();
	landscapeCreator=new LandscapeCreator();
	cur_update_pos=&update_pos1;
	prev_update_pos=&update_pos2;
	register_cur();
}
Map::~Map() {
	if(dp_map)delete dp_map;
	if(map)delete map;
	if(map_segs)delete map_segs;
	delete cube_out_of_edge;
	delete cube_null;
	delete cube_water;
	delete all_cubes;
	delete landscapeCreator;
}
void Map::swap_update_pos(){
	std::swap(update_pos1,update_pos2);
}
void Map::init(){
	if(map)delete map;
	if(dp_map)delete dp_map;

	map=new Tim::Array3D<unsigned char>(map_size.x,map_size.y,map_size.z);
	gen_map_seg();
	dp_map=new DisplayMap(this);
}
void Map::gen_map_seg(){
	static const int size_per_sig=15;
	//seg.x=((double)map->get_size().x/size_per_sig)+0.5;
	seg.x=ceil((double)get_size().x/size_per_sig);
	seg.y=1;
	//seg.z=((double)map->get_size().z/size_per_sig)+0.5;
	seg.z=ceil((double)get_size().z/size_per_sig);

	if(seg.x<1)seg.x=1;
	if(seg.y<1)seg.y=1;
	if(seg.z<1)seg.z=1;

	segsize.x = ceil((double)get_size().x / (double)seg.x);
	segsize.y = get_size().y;
	segsize.z = ceil((double)get_size().z / (double)seg.z);
	if(map_segs)delete map_segs;
	map_segs=new Tim::Array2D<MapSeg>(seg.x,seg.z);
	for(int i=0;i<seg.x;i++){
		for(int j=0;j<seg.z;j++){
			map_segs->get(i,j).init(this,glm::ivec2(i*segsize.x,j*segsize.z));
		}
	}
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
void Map::gen_sand(unsigned char &type,const double &x,const double &y,const double &z){

}
void Map::gen_cube_type(int i,int j,int k,
		const double &stone_height,
		const double &height,const double &wetness){
	unsigned char type;
	double x=((double)i/300);
	double y=((double)j/map_size.y);
	double z=((double)k/300);

	if(j<stone_height*ground_height){
		type=Cube::stone;
	}else{
		double type_val=0.8*noise.noise(x,y,z,0.01)+0.2*noise.noise(x,y,z,0.03);
		if(type_val<0.3){
			type=Cube::cubeNull;
		}else if(noise.noise(x,y,z,0.01)<0.4){
			type=Cube::stone;
		}else if(wetness<0.45&&
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
		gen_sand(type,i,j,k);
	}
	//map->get(i,j,k).set(type);
	map->get(i,j,k)=type;
}
void Map::gen_land_scape(int i,int j,int k,
		const double &stone_height,const double &height,
		const double &wetness){
	double x=((double)i/300);
	double y=((map_size.y-i)/300);
	double z=((double)k/300);
	if(get_cube_type(i,j,k)==0&&get_cube_type(i,j-1,k)==Cube::grass){
		double type_val=0.6*noise.noise(x,y,z,0.05);
		type_val+=0.2*noise.noise(x,y,z,0.6);
		type_val+=0.1*noise.noise(x,y,z,1.0);
		type_val+=0.1*get_wetness(i,k,height);
		if(type_val>0.65)push_CubeEX(i,j,k,landscapeCreator->create("Tree"));
	}

}
void Map::gen_map_shape(){
	double height;
	for (int i = 0; i < map_size.x; i++) {
		for (int k = 0; k < map_size.z; k++) {
			height=get_height(i,k);
			for (int j = 0; j < map_size.y; j++) {
				if (j < ground_height * height) {
					//map->get(i, j, k).set(Cube::startcube);
					map->get(i,j,k)=Cube::startcube;
				}
			}
		}
	}
}
void Map::gen_map_cube_type(){
	double stone_height;
	double height;
	double wetness;
	for(int i=0;i<map_size.x;i++){
		for(int k=0;k<map_size.z;k++){
			height=get_height(i,k);
			stone_height=height*noise.noise(((double)i/map_size.x),
					0,((double)k/map_size.z),0.01);
			wetness=get_wetness(i,k,height);

			for(int j=0;j<map_size.y;j++){
				if(map->get(i,j,k)>=Cube::startcube){//.type
					gen_cube_type(i,j,k,stone_height,height,wetness);
				}
			}
		}
	}
}
void Map::gen_map_water(){
	///*
	int water_height=ground_height*0.5;
	//double type_val;
	//double height;
	for(int i=0;i<map_size.x;i++){
		for(int k=0;k<map_size.z;k++){
			for(int j=0;j<map_size.y;j++){
				if(!map->get(i,j,k)&&j<water_height){//&&j>=water_height-20
					//push_CubeEX(i,j,k,new Water());
					set_cube_type(i,j,k,Cube::water);
				}
			}
		}
	}
	//*/
}
void Map::gen_map_land_scape(){
	double stone_height;
	double height;
	double wetness;
	for(int i=0;i<map_size.x;i++){
		for(int k=0;k<map_size.z;k++){
			height=get_height(i,k);
			stone_height=height*noise.noise(((double)i/map_size.x),
					0,((double)k/map_size.z),0.01);
			wetness=get_wetness(i,k,height);

			for(int j=0;j<map_size.y;j++){
				gen_land_scape(i,j,k,stone_height,height,wetness);
			}
		}
	}
}
void Map::regen_map(){
	gen_map_shape();
	gen_map_water();
	gen_map_cube_type();

	gen_map_land_scape();
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

	//map=new Tim::Array3D<Cube>(map_size.x,map_size.y,map_size.z);
	init();

	noise.init(seed);
	//srand(seed);

	regen_map();
	dp_map->update_whole_map();
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
	init();
	int type;
	for(int i=0;i<map_size.x;i++){
		for(int j=0;j<map_size.y;j++){
			for(int k=0;k<map_size.z;k++){
				fscanf(fop,"%d",&type);
				map->get(i,j,k)=type;
			}
		}
	}
	dp_map->update_whole_map();
}
MapSeg* Map::get_map_seg_by_pos(int x,int z){
	return &(map_segs->get((x/segsize.x),(z/segsize.z)));
}
MapSeg* Map::get_map_seg(int x,int z){
	return &(map_segs->get(x,z));
}
void Map::push_CubeEX(int x,int y,int z,CubeEX *cube){
	if(map->get(x,y,z)!=Cube::cubeNull){
		std::cerr<<"Map::push_CubeEX fail ,cube already exist"<<std::endl;
		delete cube;
		return;
	}
	map->get(x,y,z)=cube->get_type();//.set(Cube::CubeEX);
	get_map_seg_by_pos(x,z)->push_cube(glm::ivec3(x,y,z),cube);
}
bool Map::remove_cube(int x,int y,int z){
	return set_cube_type(x,y,z,Cube::cubeNull);
}
bool Map::set_cube_type(int x,int y,int z,int type){
	if(x<0||x>=map_size.x||y<0||y>=map_size.y||z<0||z>=map_size.z){
		std::cout<<"Map::set_cube_type out of map"<<"x="<<x<<"y="<<y<<"z="<<z<<std::endl;
		return false;
	}
	unsigned char perv_type=map->get(x,y,z);
	if(perv_type==Cube::cubeEX){//.type
		get_map_seg_by_pos(x,z)->remove_cube(glm::ivec3(x,y,z));
	}
	if(perv_type==type){
		return false;
	}
	map->get(x,y,z)=type;
	prev_update_pos->push_back(glm::ivec3(x,y,z));
	dp_map->update_water_map(glm::ivec3(x,y,z));
	dp_map->update_map(glm::ivec3(x,y,z));
	return true;
}
Cube* Map::get_cube(int x,int y,int z){
	int type=get_cube_type(x,y,z);
	if(type==-1){
		return cube_out_of_edge;
	}else if(type==Cube::cubeNull){
		return cube_null;
	}else if(type==Cube::water){
		return cube_water;//get_map_seg_by_pos(x,z)->get_cube(x,y,z);
	}
	Cube *cube=0;
	if(type>=Cube::startcube){
		cube=all_cubes->get_cube(type);
	}else if(type==Cube::cubeEX){
		cube=get_map_seg_by_pos(x,z)->get_cube(x,y,z);
	}else{
		std::cout<<"Map::get_cube unknown cube type:"<<type<<std::endl;
	}
	return cube;
}
int Map::get_cube_type(const int &x,const int &y,const int &z)const{
	if(x<0||x>=map_size.x||y<0||y>=map_size.y||z<0||z>=map_size.z){
		//std::cout<<"get out of map"<<"x="<<x<<"y="<<y<<"z="<<z<<std::endl;
		return -1;
	}
	return map->get(x,y,z);//.type
	//return map->arr[map->size.y*map->size.z*pos.x+map->size.z*pos.y+pos.z].type;//for better performance
}
void Map::update_map(int x,int y,int z){
	get_cube(x,y,z)->update(x,y,z,x,y,z);
	get_cube(x+1,y,z)->update(x+1,y,z,x,y,z);
	get_cube(x-1,y,z)->update(x-1,y,z,x,y,z);
	get_cube(x,y+1,z)->update(x,y+1,z,x,y,z);
	get_cube(x,y-1,z)->update(x,y-1,z,x,y,z);
	get_cube(x,y,z+1)->update(x,y,z+1,x,y,z);
	get_cube(x,y,z-1)->update(x,y,z-1,x,y,z);
}
void Map::update(){
	int x,y,z;
	swap_update_pos();
	for(unsigned i=0;i<cur_update_pos->size();i++){
		x=cur_update_pos->at(i).x;
		y=cur_update_pos->at(i).y;
		z=cur_update_pos->at(i).z;
		update_map(x,y,z);
	}
	cur_update_pos->clear();

}
