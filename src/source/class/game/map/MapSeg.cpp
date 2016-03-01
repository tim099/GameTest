#include "class/game/map/MapSeg.h"
#include "class/game/map/Map.h"
#include "class/game/map/cube/CubeEX.h"
MapSeg::MapSeg() {
	map=0;
}
void MapSeg::init(Map* _map,glm::ivec2 _seg_at){
	map=_map;
	seg_at=_seg_at;
	segsize=map->segsize;
}
MapSeg::~MapSeg() {

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
void MapSeg::draw(int max_y){
	CubeEX* cube;
	std::map<unsigned,CubeEX*>*map=cubes.get_map();
	typename std::map<unsigned,CubeEX*>::iterator it = map->begin();
	while(it!=map->end()){
		cube=it->second;
		if(cube->draw_cube()){
			//glm::ivec3 pos=convert_pos(p);
			if(convert_pos(it->first).y<=max_y){
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
