#ifndef CUBE_H_
#define CUBE_H_
#include "class/game/map/cube/CubeEX.h"
#include <vector>

class Cube {
	static bool cube_inited;

public:
	static std::vector<unsigned char>basic_cubes;
	static const unsigned char CubeEX=1;
	static unsigned char startcube;//has the number at the start of the basic cube
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
	unsigned char type;
private:
	static void create_basic_cubes();
	//CubeEX *cubeEX;
};

#endif /* CUBE_H_ */
