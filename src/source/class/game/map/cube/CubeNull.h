#ifndef SOURCE_CLASS_GAME_MAP_CUBE_CUBENULL_H_
#define SOURCE_CLASS_GAME_MAP_CUBE_CUBENULL_H_

#include "class/game/map/cube/Cube.h"

class CubeNull: public Cube {
public:
	CubeNull();
	virtual ~CubeNull();
	virtual std::string get_name()const{
		return "CubeNull";
	}
};

#endif /* SOURCE_CLASS_GAME_MAP_CUBE_CUBENULL_H_ */
