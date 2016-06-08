#ifndef _CUBE_H_
#define _CUBE_H_
#include <vector>
#include <string>

namespace physic{
	class RigidBody;
}
namespace AOC{
class CubeEX;
class Cube {
	static bool cube_inited;
public:
	static std::vector<unsigned char>basic_cubes;
	static const int cubeOutofEdge=-1;
	static const unsigned char cubeNull=0;
	static const unsigned char cubeEX=1;
	static const unsigned char water=2;
	static const unsigned char cube_start=3;//the number at the start of the basic cube
	static unsigned char cube_end;
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

	virtual AOC::CubeEX* get_cubeEX(){
		return 0;
	}
	virtual unsigned char get_type(){
		return 0;
	}
	virtual bool standable(){
		return false;
	}
	virtual bool jumpable(){
		return false;
	}
	virtual void collide(physic::RigidBody *b){}
	/*
	 * x,y,z is the position of this cube and
	 * ux,uy,uz is the position of the update cube
	 */
	virtual void update(int x,int y,int z,int ux,int uy,int uz);
private:
	static void create_basic_cubes();
};
}
#endif /* CUBE_H_ */
