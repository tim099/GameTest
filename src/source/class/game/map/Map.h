#ifndef MAP_H_
#define MAP_H_

#include "class/tim/array/Array3D.h"
#include "class/tim/array/Array2D.h"
#include <glm/glm.hpp>
#include <string>
#include <cmath>
#include "class/tim/math/PerlinNoise.h"
#include "class/tim/globalObject/GlobalObject.h"
#include "class/game/map/cube/Cube.h"
#include "class/game/map/MapSeg.h"
class CubeEX;
class CubeOutOfEdge;
class Water;
class CubeNull;
class CubeError;
class AllCubes;
class LandscapeCreator;
class DisplayMap;
class Timer;
class Map : public Tim::GlobalObject<Map>{

public:
	static const int MX=5000,MY=5000,MZ=5000;
	static const double CUBE_SIZE=1.0;

	Map();
	virtual ~Map();
	void init();
	void gen_map(glm::ivec3 map_size,unsigned seed,int ground_height=150);

	//ground height limited the max height of the ground
	void regen_map();
	static glm::ivec3 convert_position(glm::vec3 pos);
	void save_map(std::string path);
	void load_map(std::string path);
	void push_CubeEX(int x,int y,int z,CubeEX *cube);

	bool set_cube_type(int x,int y,int z,int val);
	bool remove_cube(int x,int y,int z);
	int get_cube_type(const int &x,const int &y,const int &z)const;
	Cube *get_cube(int x,int y,int z);

	//get map_seg by position x and z
	inline MapSeg* get_map_seg_by_pos(int x,int z){
		return &(map_segs->get((x/segsize.x),(z/segsize.z)));
	}

	//directly get map_seg
	inline MapSeg* get_map_seg(int x,int z){
		return &(map_segs->get(x,z));
	}

	void update(Timer* timer);
	glm::ivec3 get_size()const;

	inline double get_wetness(const int &i,const int &k,const double &height){
		return 0.6*height+0.4*noise.noise(((double)i/300.0),
				0.5,((double)k/300.0),0.01);
	}
	inline double get_temperature(const int &i,const int &j,const int &k){
		return 0.5*(1.0-(double)j/300.0)+
				0.2*(1.0-(double)k/300.0)+
				0.3*noise.noise(((double)i/300.0),0.5,((double)k/300.0),0.01);
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
	int get_water_height()const{
		return ground_height*water_height;
	}
	//cube being selected by mouse
	glm::ivec3 selected_cube;

	//cube being selected on(may near by the selected cube or equal to selected cube
	glm::ivec3 selected_on;

	glm::ivec3 seg;
	glm::ivec3 segsize;


	DisplayMap* dp_map;
protected:
	//generate the shape of the map(only generate the cube type=1,and empty space type=0
	void gen_map_seg();

	void gen_map_shape();
	void gen_map_cube_type();
	void gen_map_water();
	void gen_map_land_scape();

	void gen_cube_type(int i,int j,int k,
			const double &stone_height,const double &height,
			const double &wetness);
	void gen_land_scape(int i,int j,int k,
			const double &stone_height,const double &height,
			const double &wetness);

	void gen_dirt(unsigned char &type,const int &i,const int &j,const int &k);
	void gen_stone(unsigned char &type,const double &x,const double &y,const double &z);
	void gen_sand(unsigned char &type,const double &x,const double &y,const double &z);
	void swap_update_pos();
	void update_map(int x,int y,int z);

	void push_update_cube(int x,int y,int z);

	void save_update_pos(FILE * file);
	void load_update_pos(FILE * file);

	void find_select_cube();
	void find_selected_on(glm::vec3 pos);
	void find_selected_cube(glm::vec3 pos);
	//Tim::Array3D<Cube> *map;
	Tim::Array3D<unsigned char> *map;
	Tim::Array2D<MapSeg>* map_segs;
	std::vector<glm::ivec3>* cur_update_pos;
	std::vector<glm::ivec3>* prev_update_pos;
	std::vector<glm::ivec3> update_pos1;
	std::vector<glm::ivec3> update_pos2;
	glm::ivec3 map_size;

	int times;
	int ground_height;
	unsigned seed;
	double water_height;
	CubeOutOfEdge *cube_out_of_edge;
	CubeNull *cube_null;
	CubeError *cube_error;
	Water *cube_water;

	AllCubes *all_cubes;
	//LandscapeCreator *landscapeCreator;
	PerlinNoise noise;
};

#endif /* MAP_H_ */
