#ifndef MAP_H_
#define MAP_H_
#include "class/game/map/cube/Cube.h"
#include "class/tim/array/Array3D.h"
#include <glm/glm.hpp>
#include <string>
#include <cmath>
#include "class/tim/math/PerlinNoise.h"
class Map {

public:
	static const int MX=5000,MY=5000,MZ=5000;
	static const double CUBE_SIZE=1.0;
	Map();
	virtual ~Map();
	void gen_map(glm::ivec3 map_size,unsigned seed,int ground_height=150);

	//ground height limited the max height of the ground
	void regen_map();
	static glm::ivec3 convert_position(glm::vec3 pos);
	void save_map(std::string path);
	void load_map(std::string path);
	bool set_cube_type(int x,int y,int z,int val);
	int get_cube_type(const int &x,const int &y,const int &z)const;
	void update();
	glm::ivec3 get_size()const;

	inline double get_wetness(const int &i,const int &k,const double &height){
		return 0.6*height+0.4*noise.noise(((double)i/map_size.x),
				0.5,((double)k/map_size.z),0.01);
	}
	double get_height(const int &i,const int &k){
		double h1,h2,h3,h4,del_val,del_val2;
		glm::vec2 pos;
		pos = glm::vec2((double) i / 300.0, (double) k / 300.0);
		h1 = noise.noise(pos.x, pos.y, 0, 0.01);
		h2 = noise.noise(pos.x, pos.y, 0, 0.02);
		h3 = noise.noise(pos.x, pos.y, 0, 0.05);
		h4 =noise.noise(pos.x, pos.y,0,0.1);
		del_val=noise.noise(pos.x,0,pos.y,0.01);
		del_val2=noise.noise(pos.x,0,pos.y,0.001);
		return 0.5+((0.6+0.4*del_val2)
				*(0.65*h1+0.25*h2+0.1*h3+0.05*del_val*h4-0.5));
	}
	//get the temperature(value between 0.0~1.0
	double get_temperature(const int &i,const double &height){
		double temperature=0.5*(1.0-((double)i/map_size.x));//alter by latitude
		temperature+=-0.5*height;
		return temperature;
	}
protected:
	//generate the shape of the map(only generate the cube type=1,and empty space type=0
	void gen_map_shape();


	void gen_cube_type(int i,int j,int k,
			const double &stone_height,const double &height,
			const double &wetness);
	void gen_dirt(unsigned char &type,const int &i,const int &j,const int &k);
	void gen_stone(unsigned char &type,const double &x,const double &y,
			const double &z);
	Tim::Array3D<Cube> *map;
	glm::ivec3 map_size;
	int times;
	int ground_height;
	unsigned seed;

	PerlinNoise noise;
};

#endif /* MAP_H_ */
