#include "class/game/ageOfCube/map/attack/missile/CubeMissileLauncher.h"
#include "class/display/draw/drawObject/AllDrawObjects.h"
namespace AOC {

CubeMissileLauncher::CubeMissileLauncher() {
	attack_range=20.0;
}
CubeMissileLauncher::~CubeMissileLauncher() {

}
void CubeMissileLauncher::draw_weapon(){
	/*
	Display::DrawObject* dobj=Display::AllDrawObjects::get_cur_object()->get("attack/cube_missile_1");
	math::Position *dp_pos=new math::Position();//
	math::vec3<double> atk_pos=get_attack_pos();
	dp_pos->set_pos(glm::vec3(atk_pos.x,atk_pos.y,atk_pos.z));
	dp_pos->set_scale(glm::vec3(attack_size,attack_size,attack_size));

	dobj->push_temp_drawdata(new Display::DrawDataObj(dp_pos,true,true));
	*/
}
} /* namespace AOC */
