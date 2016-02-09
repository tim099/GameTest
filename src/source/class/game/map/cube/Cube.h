#ifndef CUBE_H_
#define CUBE_H_
#include "class/game/map/cube/CubeEX.h"
#include <vector>

class Cube {
	static bool cube_inited;

public:
	static std::vector<unsigned char>basic_cubes;
	static unsigned char stone;
	static unsigned char dirt;
	static unsigned char sand;
	static unsigned char grass;
	static unsigned char coal;
	static void Cube_init();

	Cube(unsigned char type);
	Cube();
	virtual ~Cube();
	void set(unsigned char type);
	void set_EX(CubeEX *cubeEX);
	unsigned char type;
private:
	static void create_basic_cubes();
	CubeEX *cubeEX;
};

#endif /* CUBE_H_ */
