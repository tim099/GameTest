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
void CubeMissile::draw_attack(){
	//Display::DrawObject *missile_Drawobj=Display::AllDrawObjects::get_cur_object()->get("attack/ball_missile_1");
	Display::DrawObject *missile_Drawobj=Display::AllDrawObjects::get_cur_object()->get("attack/cube_missile_1");
	math::Position *dp_pos=new math::Position();
	dp_pos->set_pos(glm::vec3(pos.x,pos.y,pos.z));
	dp_pos->set_scale(glm::vec3(2*radius,2*radius,2*radius));
	missile_Drawobj->push_temp_drawdata(new Display::DrawDataObj(dp_pos,true,true));
}
} /* namespace AOC */
