#ifndef MAP_H_
#define MAP_H_
#include "class/game/map/cube/Cube.h"
#include <glm/glm.hpp>
static const int MX=300,MY=100,MZ=300;
class Map {
public:
	Map();
	virtual ~Map();
	void load_map(const char *path);
	void set(int x,int y,int z,int val);
	int get(int x,int y,int z)const;

protected:
	bool end;
	Cube* map[MX][MY][MZ];
	glm::ivec3 ms;
};

#endif /* MAP_H_ */
