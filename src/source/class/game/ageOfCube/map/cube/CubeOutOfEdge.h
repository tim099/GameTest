#ifndef SOURCE_CLASS_GAME_MAP_CUBE_CUBEOUTOFEDGE_H_
#define SOURCE_CLASS_GAME_MAP_CUBE_CUBEOUTOFEDGE_H_

#include "class/game/ageOfCube/map/cube/Cube.h"
namespace AOC{
class CubeOutOfEdge: public AOC::Cube {
public:
	CubeOutOfEdge();
	virtual ~CubeOutOfEdge();
	virtual std::string get_name()const{
		return "CubeOutOfEdge";
	}
};
}
#endif /* SOURCE_CLASS_GAME_MAP_CUBE_CUBEOUTOFEDGE_H_ */
