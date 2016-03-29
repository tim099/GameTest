#include "class/game/map/cube/AllCubes.h"
#include "class/game/map/cube/Cube.h"
#include "class/game/map/landscape/Landscape.h"

#include "class/game/map/cube/basic/stone/Stone.h"
#include "class/game/map/cube/basic/dirt/Dirt.h"
#include "class/game/map/cube/basic/sand/Sand.h"

#include "class/game/map/cube/basic/dirt/Grass.h"
#include "class/game/map/cube/basic/stone/Coal.h"
AllCubes::AllCubes() {
	Cube::Cube_init();
	//Landscape::Landscape_init();
	push(new Stone());

	push(new Dirt());

	push(new Sand());

	push(new Grass());
	push(new Coal());
}
AllCubes::~AllCubes() {

}
void AllCubes::push(Cube* cube){
	cubes.push(cube->get_type(),cube);
}
Cube* AllCubes::get_cube(unsigned char type){
	return cubes.get(type);
}
