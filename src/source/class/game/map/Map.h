#ifndef MAP_H_
#define MAP_H_
#include "class/game/map/cube/Cube.h"
#include "class/tim/array/Array3D.h"
#include <glm/glm.hpp>
#include <string>
class Map {
public:
	static const int MX=5000,MY=5000,MZ=5000;
	static const double CUBE_SIZE=1.0;
	Map();
	virtual ~Map();
	void gen_map(glm::ivec3 map_size,unsigned seed);
	static glm::ivec3 convert_position(glm::vec3 pos);
	void save_map(std::string path);
	void load_map(std::string path);
	bool set_cube_type(int x,int y,int z,int val);
	int get_cube_type(const int &x,const int &y,const int &z)const;
	void update();
	glm::ivec3 get_size()const;
protected:
	Tim::Array3D<Cube> *map;
	glm::ivec3 map_size;
	unsigned seed;
};

#endif /* MAP_H_ */
