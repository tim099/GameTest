#include "class/game/ageOfCube/map/building/tower/LaserTower.h"
#include "class/display/draw/drawObject/AllDrawObjects.h"
#include "class/game/ageOfCube/map/attack/weapon/WeaponCreator.h"
namespace AOC {
void LaserTower::building_pre_init(){

}
LaserTower::LaserTower() {
	size=6.0;
}
LaserTower::LaserTower(LaserTower* tower){
	init(3000,0);
	size=tower->size;
	set_attack_cycle(30);
	//attack_damage=5;

	Weapon* weapon=WeaponCreator::get_cur_object()->create("LaserCannon");
	weapon->set_attack_range(11.0);
	weapon->set_attack_damage(5);
	push_weapon(weapon);
	build_cost = ResourceModifier("cube",-50);
}
LaserTower::~LaserTower() {

}
void LaserTower::save_building(FILE * file){
	//fprintf(file,"%d\n",timer);
}
void LaserTower::load_building(FILE * file){
	//fscanf(file,"%d\n",&timer);
}
void LaserTower::building_update(){
	//attack_update();
}
void LaserTower::draw_building(){
	math::vec3<int> real_size=get_cube_large_size();
	Display::DrawObject* tower_Drawobj=Display::AllDrawObjects::get_cur_object()->get("building/laser_tower");
	tower_Drawobj->push_temp_drawdata(new Display::DrawDataObj(&pos));

}
} /* namespace AOC */
