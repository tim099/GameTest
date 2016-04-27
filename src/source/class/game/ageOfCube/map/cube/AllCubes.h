#ifndef SOURCE_CLASS_GAME_MAP_CUBE_ALLCUBES_H_
#define SOURCE_CLASS_GAME_MAP_CUBE_ALLCUBES_H_
#include "class/tim/map/MapContainer.h"
namespace AOC{
class Cube;
class AllCubes {
public:
	AllCubes();
	virtual ~AllCubes();
	inline Cube* get_cube(unsigned char type){
		return cubes.get(type);
	}
protected:
	void push(Cube* cube);
	Tim::MapContainer<unsigned char,Cube>cubes;
};
}
#endif /* SOURCE_CLASS_GAME_MAP_CUBE_ALLCUBES_H_ */
