#ifndef _CUBE_H_
#define _CUBE_H_
#include <vector>
#include <string>

class CubeEX;
class Cube {
	static bool cube_inited;
public:
	static std::vector<unsigned char>basic_cubes;
	static const int cubeOutofEdge=-1;
	static const unsigned char cubeNull=0;
	static const unsigned char cubeEX=1;
	static const unsigned char water=2;
	static const unsigned char startcube=3;//has the number at the start of the basic cube
	static unsigned char stone;
	static unsigned char dirt;
	static unsigned char sand;
	static unsigned char grass;
	static unsigned char coal;
	/*
	 * this function will be called while class Map constructed
	 */
	static void Cube_init();

	Cube();
	virtual ~Cube();
	virtual std::string get_name()const{
		return "Cube";
	}

	virtual CubeEX* get_cubeEX(){
		return 0;
	}
	virtual unsigned char get_type(){
		return 0;
	}
	/*
	 * x,y,z is the position of this cube and
	 * ux,uy,uz is the position of the update cube
	 */
	virtual void update(int x,int y,int z,int ux,int uy,int uz);
private:
	static void create_basic_cubes();
};

#endif /* CUBE_H_ */
