#ifndef SOURCE_CLASS_GAME_MAP_MAPSEG_H_
#define SOURCE_CLASS_GAME_MAP_MAPSEG_H_
#include <glm/glm.hpp>
#include "class/game/map/cube/CubeEX.h"
#include "class/tim/map/MapContainer.h"
class Map;
class MapSeg {
public:
	MapSeg();
	virtual ~MapSeg();
	void init(Map* map,glm::ivec2 seg_at);
	void draw();
	void push_cube(glm::ivec3 pos,CubeEX *cube);
	void remove_cube(glm::ivec3 pos);
	glm::ivec2 seg_at;//start position's x and z
protected:
	unsigned convert_pos(const glm::ivec3 &pos);
	Tim::MapContainer<unsigned,CubeEX>cubes;
	Map* map;
	glm::ivec3 segsize;
};

#endif /* SOURCE_CLASS_GAME_MAP_MAPSEG_H_ */
