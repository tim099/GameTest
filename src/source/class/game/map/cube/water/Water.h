#ifndef SOURCE_CLASS_GAME_MAP_CUBE_WATER_WATER_H_
#define SOURCE_CLASS_GAME_MAP_CUBE_WATER_WATER_H_

#include "class/game/map/cube/liquid/CubeLiquid.h"

class Water: public CubeLiquid {
public:
	virtual std::string get_name()const{
		return "Water";
	}
	virtual unsigned char get_type(){
		return Cube::water;
	}
	/*
	 * check if cube type is water
	 */
	inline static bool is_water(int type){
		if(type==Cube::water)return true;
		return false;
	}
	Water();
	virtual ~Water();
protected:

};

#endif /* SOURCE_CLASS_GAME_MAP_CUBE_WATER_WATER_H_ */
