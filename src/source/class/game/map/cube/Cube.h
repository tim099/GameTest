#ifndef CUBE_H_
#define CUBE_H_
#include "class/game/map/cube/CubeEX.h"
class Cube {
public:
	Cube(unsigned char type);
	Cube();
	virtual ~Cube();
	void set(unsigned char type);
	void set(CubeEX *cubeEX);
	unsigned char type;
private:


	CubeEX *cubeEX;
};

#endif /* CUBE_H_ */
