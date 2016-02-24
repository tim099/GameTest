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
CubeEX* MapSeg::get_cube(int x,int y,int z){
	return cubes.get(convert_pos(glm::ivec3(x,y,z)));
}
void MapSeg::draw(int max_y){
	CubeEX* cube;
	for(unsigned i=0;i<cubes_to_draw.size();i++){
		cube=cubes_to_draw.at(i);
		if(cube->get_y()<=max_y){
			cube->draw();
		}
	}
}
void MapSeg::push_cube(glm::ivec3 pos,CubeEX *cube){
	cube->set_pos(pos.x,pos.y,pos.z);
	cubes.push(convert_pos(pos),cube);
	if(cube->draw_cube())push_cube_to_draw(cube);
}
void MapSeg::remove_cube(glm::ivec3 pos){
	CubeEX *cube=cubes.get(convert_pos(pos));
	if(cube->draw_cube())remove_cube_to_draw(cube);
	cubes.remove(convert_pos(pos));
}
void MapSeg::push_cube_to_draw(CubeEX *cube){
	cubes_to_draw.push_back(cube);
}
void MapSeg::remove_cube_to_draw(CubeEX *cube){
	for(unsigned i=0;i<cubes_to_draw.size();i++){
		if(cubes_to_draw.at(i)==cube){
			cubes_to_draw.at(i)=cubes_to_draw.back();
			cubes_to_draw.pop_back();
		}
	}
}
