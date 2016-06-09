#include "class/game/ageOfCube/map/attack/missile/Missile.h"
#include "class/display/draw/drawObject/AllDrawObjects.h"
namespace AOC {
void Missile::attack_pre_init(){
	missile_Drawobj=Display::AllDrawObjects::get_cur_object()->get("building/ball_spawn_tower_part_4");
}
Missile::Missile() {
	missile_Drawobj=0;
}
Missile::Missile(Missile* missile){
	missile_Drawobj=missile->missile_Drawobj;
}
Missile::~Missile() {

}
void Missile::draw_attack(){

}
void Missile::attack_update(){

}
} /* namespace AOC */
