#ifndef SOURCE_CLASS_GAME_MAP_CUBE_CUBEERROR_H_
#define SOURCE_CLASS_GAME_MAP_CUBE_CUBEERROR_H_

#include "class/game/map/cube/Cube.h"

class CubeError: public Cube {
public:
	CubeError();
	virtual ~CubeError();
	virtual std::string get_name()const{
		return "CubeError";
	}
};

#endif /* SOURCE_CLASS_GAME_MAP_CUBE_CUBEERROR_H_ */
