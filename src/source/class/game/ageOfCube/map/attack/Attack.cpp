#include "class/game/ageOfCube/map/attack/Attack.h"
#include "class/game/ageOfCube/map/attack/AttackController.h"
namespace AOC {

Attack::Attack() {
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
} /* namespace AOC */
