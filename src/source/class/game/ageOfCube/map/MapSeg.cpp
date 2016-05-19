#include "class/game/ageOfCube/map/MapSeg.h"
#include "class/game/ageOfCube/map/Map.h"
#include "class/game/ageOfCube/map/cube/CubeEX.h"
#include "class/game/ageOfCube/map/landscape/Landscape.h"
#include "class/game/ageOfCube/map/landscape/LandscapeCreator.h"
#include "class/game/ageOfCube/map/cube/CubeLarge.h"
#include "class/game/ageOfCube/map/cube/AttachCube.h"
#include <cstdio>
namespace AOC{
MapSeg::MapSeg() {
	map=0;
	updated=false;
}
void MapSeg::init(Map* _map,math::vec2<int> _seg_at){
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
void MapSeg::update(){
	//std::cout<<"MapSeg::update() 1"<<std::endl;
	update_landscape();
	//std::cout<<"MapSeg::update() 2"<<std::endl;
}
void MapSeg::update_landscape(){
	CubeEX* cube;
	Landscape* lc;
	std::vector<Landscape*> lcs;
	std::vector<math::vec3<int> > lcs_pos;
	std::map<unsigned,CubeEX*>*map=cubes.get_map();
	typename std::map<unsigned,CubeEX*>::iterator it = map->begin();
	while(it!=map->end()){
		cube=it->second;
		lc=cube->get_landscape();
		if(lc){
			lc->update();
		}
		it++;
	}
}
void MapSeg::save_landscape(FILE * file){
	CubeEX* cube;
	Landscape* lc;
	std::vector<Landscape*> lcs;
	std::vector<math::vec3<int> > lcs_pos;
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
		lc->build(map,pos.x,pos.y,pos.z);
		//map->push_CubeEX(pos.x,pos.y,pos.z,lc);
	}
}
unsigned MapSeg::convert_pos(const math::vec3<int> &pos){
	return (pos.x-seg_at.x)+pos.y*segsize.x+(pos.z-seg_at.y)*segsize.x*segsize.y;
}
math::vec3<int> MapSeg::convert_pos(unsigned p){
	math::vec3<int> pos;
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
	return cubes.get(convert_pos(math::vec3<int>(x,y,z)));
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
void MapSeg::push_cube(math::vec3<int> pos,CubeEX *cube){
	cube->set_pos(pos.x,pos.y,pos.z);
	cubes.push(convert_pos(pos),cube);
}
void MapSeg::remove_cube(math::vec3<int> pos){
	CubeEX* cube=get_cube(pos.x,pos.y,pos.z);
	if(cube){
		cube->remove();
		cubes.remove(convert_pos(pos));
	}

}
}
