#ifndef SOURCE_CLASS_GAME_MAP_CUBE_CUBENULL_H_
#define SOURCE_CLASS_GAME_MAP_CUBE_CUBENULL_H_

#include "class/game/ageOfCube/map/cube/Cube.h"
namespace AOC{
class CubeNull: public Cube {
public:
	CubeNull();
	virtual ~CubeNull();
	virtual std::string get_name()const{
		return "CubeNull";
	}
	virtual bool standable(){
		return false;
	}
	virtual bool jumpable(){
		return false;
	}
};
}
#endif /* SOURCE_CLASS_GAME_MAP_CUBE_CUBENULL_H_ */
