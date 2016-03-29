#include "class/game/map/MapSeg.h"
#include "class/game/map/Map.h"
#include "class/game/map/cube/CubeEX.h"
#include "class/game/map/landscape/Landscape.h"
#include "class/game/map/landscape/LandscapeCreator.h"
#include <cstdio>
MapSeg::MapSeg() {
	map=0;
	updated=false;
}
void MapSeg::init(Map* _map,glm::ivec2 _seg_at){
	map=_map;
	seg_at=_seg_at;
	segsize=map->segsize;
}
MapSeg::~MapSeg() {

}
void MapSeg::save(FILE * file){
	save_landscape(file);
}
void MapSeg::load(FILE * file){
	load_landscape(file);
}
void MapSeg::save_landscape(FILE * file){
	CubeEX* cube;
	Landscape* lc;
	std::vector<Landscape*> lcs;
	std::vector<glm::ivec3> lcs_pos;
	std::map<unsigned,CubeEX*>*map=cubes.get_map();
	typename std::map<unsigned,CubeEX*>::iterator it = map->begin();
	while(it!=map->end()){
		cube=it->second;
		lc=cube->get_landscape();
		if(lc){
			lcs_pos.push_back(convert_pos(it->first));
			lcs.push_back(lc);
		}
		it++;
	}
	fprintf(file,"%u\n",lcs.size());
	for(unsigned i=0;i<lcs.size();i++){
		fprintf(file,"%d,%d,%d\n",lcs_pos.at(i).x,lcs_pos.at(i).y,lcs_pos.at(i).z);
		lcs.at(i)->save(file);
	}
}
void MapSeg::load_landscape(FILE * file){
	LandscapeCreator* creator=LandscapeCreator::get_cur_object();
	unsigned landscape_size;
	fscanf(file,"%u\n",&landscape_size);
	//std::cout<<"MapSeg::load_landscape size="<<landscape_size<<std::endl;
	char name[100];
	Landscape* lc;
	glm::ivec3 pos;
	for(unsigned i=0;i<landscape_size;i++){
		fscanf(file,"%d,%d,%d\n",&pos.x,&pos.y,&pos.z);
		//std::cout<<"MapSeg::load_landscape pos:"<<pos.x<<","<<pos.y<<","<<pos.z<<std::endl;
		fscanf(file,"%s\n",name);
		//std::cout<<"MapSeg::load_landscape name:"<<name<<std::endl;
		lc=creator->create(name);
		lc->load(file);
		map->push_CubeEX(pos.x,pos.y,pos.z,lc);
	}
}
unsigned MapSeg::convert_pos(const glm::ivec3 &pos){
	return (pos.x-seg_at.x)+pos.y*segsize.x+(pos.z-seg_at.y)*segsize.x*segsize.y;
}
glm::ivec3 MapSeg::convert_pos(unsigned p){
	glm::ivec3 pos;
	pos.x=p%segsize.x;
	p=p/segsize.x;
	pos.y=p%segsize.y;
	p/=segsize.y;
	pos.z=p;
	pos.x+=seg_at.x;
	pos.z+=seg_at.y;
	return pos;
}
CubeEX* MapSeg::get_cube(int x,int y,int z){
	return cubes.get(convert_pos(glm::ivec3(x,y,z)));
}
void MapSeg::draw(int display_height){
	CubeEX* cube;
	std::map<unsigned,CubeEX*>*map=cubes.get_map();
	typename std::map<unsigned,CubeEX*>::iterator it = map->begin();
	while(it!=map->end()){
		cube=it->second;
		if(cube->draw_cube()){
			if(convert_pos(it->first).y<display_height){
				cube->draw();
			}
		}
		it++;
	}
}
void MapSeg::push_cube(glm::ivec3 pos,CubeEX *cube){
	cube->set_pos(pos.x,pos.y,pos.z);
	cubes.push(convert_pos(pos),cube);
}
void MapSeg::remove_cube(glm::ivec3 pos){
	cubes.remove(convert_pos(pos));
}
