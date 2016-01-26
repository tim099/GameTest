#ifndef MAP_H_
#define MAP_H_
#include "class/game/map/cube/Cube.h"
#include "class/tim/array/Array3D.h"
#include <glm/glm.hpp>
#include <string>
class Map {
public:
	static const int MX=300,MY=100,MZ=300;
	static const double CUBE_SIZE=1.0;
	Map();
	virtual ~Map();

	static glm::ivec3 convert_position(glm::vec3 pos);
	void load_map(std::string path);
	bool set(int x,int y,int z,int val);
	int get(const int &x,const int &y,const int &z)const;
	void tic();
protected:
	Tim::Array3D<Cube> *map;
	glm::ivec3 ms;
};

#endif /* MAP_H_ */
