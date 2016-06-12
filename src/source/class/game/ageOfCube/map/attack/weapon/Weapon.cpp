#include "class/game/ageOfCube/map/attack/weapon/Weapon.h"
#include "class/game/ageOfCube/map/unit/Unit.h"
#include "class/game/ageOfCube/map/unit/UnitController.h"
#include "class/game/ageOfCube/map/attack/AttackCreator.h"
namespace AOC {

Weapon::Weapon() {
	attack_timer=0;
	attack_cycle=300;
	unit=0;
}
Weapon::~Weapon() {

}
void Weapon::save(FILE* file){
	fprintf(file,"%d %d\n",attack_timer,attack_cycle);
}
void Weapon::load(FILE* file){
	fscanf(file,"%d %d\n",&attack_timer,&attack_cycle);
}
bool Weapon::attack(){
	bool attack_success=false;
	if(attack_timer>attack_cycle){
		Unit* target;
		unsigned enemy_id=(unit->get_player()==0?1:0);
		target=UnitController::get_cur_object()->search_unit(enemy_id,unit->get_attack_pos());
		if(target&&(target->get_pos()-unit->get_pos()).get_length()<unit->get_attack_range()){
			fire(target);
			attack_timer=0;
			attack_success=true;
		}else{
			attack_timer*=0.8;
		}
	}
	return attack_success;
}
void Weapon::fire(Unit* target){
	if(!target)return;
	//std::cout<<"Ball::attack(Unit* target)"<<std::endl;
	Attack* attack=AttackCreator::get_cur_object()->create(unit->get_attack_type());
	attack->radius=0.5*unit->get_attack_size();

	attack->pos=unit->get_attack_pos();
	attack->set_target(target);
	attack->set_damage(unit->attack_damage);
	attack->create_attack();
}
void Weapon::update(){
	if(!unit)return;

	attack_timer++;
	if(attack_timer>attack_cycle){
		if(attack()){
			attack_timer=0;
		}else{//attack false
			attack_timer*=0.8;
		}
	}

	attack_timer++;


	weapon_update();
}
} /* namespace AOC */
