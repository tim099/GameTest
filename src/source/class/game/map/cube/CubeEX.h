#ifndef SOURCE_CLASS_GAME_MAP_CUBE_CUBEEX_H_
#define SOURCE_CLASS_GAME_MAP_CUBE_CUBEEX_H_

#include "class/game/map/cube/Cube.h"
#include <string>
class CubeEX : public Cube{
public:
	CubeEX();
	virtual ~CubeEX();

	//return true id this cube needed to be draw
	virtual bool draw_cube(){
		return false;
	}
	virtual CubeEX* get_cubeEX(){
		return this;
	}
	virtual std::string get_name()const{
		return "CubeEX";
	}
	virtual unsigned char get_type(){
		return Cube::cubeEX;
	}
	//this function will be called by out side when needed to draw this cube
	virtual void draw();
	void set_pos(int x,int y,int z);
	inline int get_y()const{
		return y;
	}
	int type;
protected:
	int x,y,z;
};

#endif /* SOURCE_CLASS_GAME_MAP_CUBE_CUBEEX_H_ */
