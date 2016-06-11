#include "class/game/ageOfCube/map/attack/missile/CubeMissile.h"
#include "class/display/draw/drawObject/AllDrawObjects.h"
namespace AOC {

CubeMissile::CubeMissile() {

}
CubeMissile::~CubeMissile() {

}
CubeMissile::CubeMissile(CubeMissile* cube){
	radius=cube->radius;
	timer=0;
	type=0;
}
Display::DrawObject *CubeMissile::get_missile_drawobj(){
	return Display::AllDrawObjects::get_cur_object()->get("attack/cube_missile_1");
}
} /* namespace AOC */
