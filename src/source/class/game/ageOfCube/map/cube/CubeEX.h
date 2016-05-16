#ifndef SOURCE_CLASS_GAME_MAP_CUBE_CUBEEX_H_
#define SOURCE_CLASS_GAME_MAP_CUBE_CUBEEX_H_

#include "class/game/ageOfCube/map/cube/Cube.h"
#include <string>
namespace AOC{
class Landscape;
class Building;
class CubeEX : public Cube{
public:
	CubeEX();
	virtual ~CubeEX();
	void save(FILE * file){
		save_cubeEX(file);
	}
	void load(FILE * file){
		load_cubeEX(file);
	}
	//return true id this cube needed to be draw
	virtual bool draw_cube(){
		return false;
	}
	virtual AOC::CubeEX* get_cubeEX(){
		return this;
	}
	virtual std::string get_name()const{
		return "CubeEX";
	}
	virtual unsigned char get_type(){
		return Cube::cubeEX;
	}
	virtual AOC::Landscape* get_landscape(){
		return 0;
	}
	virtual AOC::Building* get_building(){
		return 0;
	}
	//this function will be called by out side when needed to draw this cube
	virtual void draw();
	virtual void set_pos(int x,int y,int z){

	}

protected:
	virtual void save_cubeEX(FILE * file){

	}
	virtual void load_cubeEX(FILE * file){

	}
};
}
#endif /* SOURCE_CLASS_GAME_MAP_CUBE_CUBEEX_H_ */
