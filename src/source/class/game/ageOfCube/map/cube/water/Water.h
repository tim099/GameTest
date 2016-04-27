#ifndef SOURCE_CLASS_GAME_MAP_CUBE_WATER_WATER_H_
#define SOURCE_CLASS_GAME_MAP_CUBE_WATER_WATER_H_

#include "class/game/ageOfCube/map/cube/liquid/CubeLiquid.h"
namespace AOC{
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
	virtual void update(int x,int y,int z,int ux,int uy,int uz);
	Water();
	virtual ~Water();
protected:

};
}
#endif /* SOURCE_CLASS_GAME_MAP_CUBE_WATER_WATER_H_ */
