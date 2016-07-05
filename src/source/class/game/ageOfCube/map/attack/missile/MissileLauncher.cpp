#include "class/game/ageOfCube/map/attack/missile/MissileLauncher.h"
#include "class/display/draw/drawObject/AllDrawObjects.h"
namespace AOC {

MissileLauncher::MissileLauncher() {

}
MissileLauncher::~MissileLauncher() {

}
void MissileLauncher::weapon_update(){

}
void MissileLauncher::draw_weapon(){
	Display::DrawObject* dobj=Display::AllDrawObjects::get_cur_object()->get("attack/missile_launcher");
	math::Position *dp_pos=new math::Position();//attack/cube_missile_1
	math::vec3<double> atk_pos=get_attack_pos();
	dp_pos->set_pos(glm::vec3(atk_pos.x,atk_pos.y,atk_pos.z));
	dp_pos->set_scale(glm::vec3(attack_size,attack_size,attack_size));
	dp_pos->set_ry(360.0*attack_timer/attack_cycle);
	math::Position *dp_pos2=new math::Position();
	dp_pos2->set_pos(glm::vec3(atk_pos.x,
			atk_pos.y-(0.35+0.2*fabs(0.5-(double)attack_timer/attack_cycle))*attack_size,atk_pos.z));
	dp_pos2->set_scale(glm::vec3(attack_size,attack_size,attack_size));

	dobj->push_temp_drawdata(new Display::DrawDataObj(dp_pos,true,true));
	dobj->push_temp_drawdata(new Display::DrawDataObj(dp_pos2,true,true));
}
} /* namespace AOC */
