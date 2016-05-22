#ifndef SOURCE_CLASS_GAME_MAP_MAPSEG_H_
#define SOURCE_CLASS_GAME_MAP_MAPSEG_H_
#include "class/tim/math/vec3.h"
#include "class/tim/math/vec2.h"
#include <vector>

#include "class/tim/map/MapContainer.h"

namespace AOC{
class CubeEX;
class Map;
class MapSeg {
public:
	MapSeg();
	virtual ~MapSeg();
	void save(FILE * file);
	void load(FILE * file);

	void init(Map* map,math::vec2<int> seg_at);
	void draw(int display_height);
	void push_cube(math::vec3<int> pos,CubeEX *cube);
	void remove_cube(math::vec3<int> pos);
	void update();
	CubeEX* get_cube(int x,int y,int z);
	math::vec2<int> seg_at;//start position's x and z
	bool updated;
protected:
	void update_landscape();
	void save_landscape(FILE * file);
	void load_landscape(FILE * file);
	void save_building(FILE * file);
	void load_building(FILE * file);
	unsigned convert_pos(const math::vec3<int> &pos);
	math::vec3<int> convert_pos(unsigned p);
	Tim::MapContainer<unsigned,CubeEX>cubes;
	Map* map;
	math::vec3<int> segsize;
};
}
#endif /* SOURCE_CLASS_GAME_MAP_MAPSEG_H_ */
