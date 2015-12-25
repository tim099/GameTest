#ifndef MAP_H_
#define MAP_H_
#include "class/game/map/cube/Cube.h"
#include <glm/glm.hpp>

class Map {
public:
	static const int MX=300,MY=100,MZ=300;
	static const double CUBE_SIZE=1.0;
	Map();
	virtual ~Map();

	static glm::ivec3 convert_position(glm::vec3 pos);
	void load_map(const char *path);
	bool set(glm::ivec3 pos,int val);
	int get(glm::ivec3 pos)const;
	void tic();
protected:
	Cube* map[MX][MY][MZ];
	glm::ivec3 ms;
};

#endif /* MAP_H_ */
