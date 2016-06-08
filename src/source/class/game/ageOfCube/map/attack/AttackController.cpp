#include "class/game/ageOfCube/map/attack/AttackController.h"
#include "class/game/ageOfCube/map/attack/AttackCreator.h"
namespace AOC {

AttackController::AttackController() {

	creator=new AttackCreator();
	register_cur();
}
AttackController::~AttackController() {
	delete creator;
}
void AttackController::update(){

}
void AttackController::save(FILE *file){

}
void AttackController::load(FILE *file){

}
} /* namespace AOC */
