#ifndef SOURCE_CLASS_GAME_MAP_CUBE_BASIC_BASICCUBE_H_
#define SOURCE_CLASS_GAME_MAP_CUBE_BASIC_BASICCUBE_H_
#include "class/game/ageOfCube/map/cube/Cube.h"
/*
 * basic cube types(EX:dirt,grass,sand..
 */



namespace AOC{
class BasicCube : public Cube{
public:
	BasicCube();
	virtual ~BasicCube();
	virtual bool standable(){
		return true;
	}
	virtual bool jumpable(){
		return true;
	}
};
}
#endif /* SOURCE_CLASS_GAME_MAP_CUBE_BASIC_BASICCUBE_H_ */
