#include "class/game/map/MapSeg.h"
#include "class/game/map/Map.h"
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
void MapSeg::draw(){
	std::map<unsigned,CubeEX*> *map=cubes.get_map();
	CubeEX* cube;
	for(std::map<unsigned,CubeEX*>::iterator it=map->begin();it!=map->end();it++){
		cube=it->second;
		cube->draw();
	}

}
void MapSeg::push_cube(glm::ivec3 pos,CubeEX *cube){
	cube->set_pos(pos.x,pos.y,pos.z);
	cubes.push(convert_pos(pos),cube);
}
void MapSeg::remove_cube(glm::ivec3 pos){
	cubes.remove(convert_pos(pos));
}
