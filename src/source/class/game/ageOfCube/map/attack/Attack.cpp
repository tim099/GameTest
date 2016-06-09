#include "class/game/ageOfCube/map/attack/Attack.h"
#include "class/game/ageOfCube/map/attack/AttackController.h"
#include "class/game/ageOfCube/map/Map.h"
#include "class/game/ageOfCube/map/DisplayMap.h"
#include "class/game/ageOfCube/map/unit/Unit.h"
namespace AOC {

Attack::Attack() {
	target=0;
	attack_created=false;
}
Attack::~Attack() {
	if(attack_created){
		AttackController::get_cur_object()->remove(this);
	}
}
void Attack::create_attack(){
	attack_created=true;
	AttackController::get_cur_object()->push(this);
}
void Attack::update(){
	set_detect_collision();
	attack_update();
}
void Attack::draw(){
	math::vec3<double> s=Map::get_cur_object()->dp_map->dp_start;
	math::vec3<double> e=Map::get_cur_object()->dp_map->dp_end;
	if(pos>=s&&pos<=e){
		draw_attack();
	}
}
} /* namespace AOC */
