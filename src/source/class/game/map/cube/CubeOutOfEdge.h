#ifndef SOURCE_CLASS_GAME_MAP_CUBE_CUBEOUTOFEDGE_H_
#define SOURCE_CLASS_GAME_MAP_CUBE_CUBEOUTOFEDGE_H_

#include "class/game/map/cube/Cube.h"

class CubeOutOfEdge: public Cube {
public:
	CubeOutOfEdge();
	virtual ~CubeOutOfEdge();
	virtual std::string get_name()const{
		return "CubeOutOfEdge";
	}
};

#endif /* SOURCE_CLASS_GAME_MAP_CUBE_CUBEOUTOFEDGE_H_ */
