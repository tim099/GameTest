#include "class/game/ageOfCube/map/building/tower/LaserTower.h"
#include "class/display/draw/drawObject/AllDrawObjects.h"
namespace AOC {
void LaserTower::building_pre_init(){

}
LaserTower::LaserTower() {
	size=6.0;
	attack_cycle=30;
	attack_damage=5;
}
LaserTower::LaserTower(LaserTower* tower){
	init(3000,0);
	size=tower->size;
	attack_cycle=tower->attack_cycle;
	attack_damage=tower->attack_damage;
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
	attack_update();
}
void LaserTower::draw_building(){
	math::vec3<int> real_size=get_cube_large_size();
	Display::DrawObject* tower_Drawobj=Display::AllDrawObjects::get_cur_object()->get("building/laser_tower");
	tower_Drawobj->push_temp_drawdata(new Display::DrawDataObj(&pos));

}
} /* namespace AOC */
