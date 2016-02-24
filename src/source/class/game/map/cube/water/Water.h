#ifndef SOURCE_CLASS_GAME_MAP_CUBE_WATER_WATER_H_
#define SOURCE_CLASS_GAME_MAP_CUBE_WATER_WATER_H_

#include "class/game/map/cube/liquid/CubeLiquid.h"

class Water: public CubeLiquid {
public:
	virtual bool draw_cube(){
		return false;
	}
	virtual void draw();
	virtual std::string get_name()const{
		return "Water";
	}
	virtual unsigned char get_type(){
		return Cube::water;
	}
	Water();
	virtual ~Water();
protected:

};

#endif /* SOURCE_CLASS_GAME_MAP_CUBE_WATER_WATER_H_ */
