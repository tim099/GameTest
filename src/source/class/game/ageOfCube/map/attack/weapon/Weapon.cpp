#include "class/game/ageOfCube/map/attack/weapon/Weapon.h"
#include "class/game/ageOfCube/map/unit/Unit.h"
#include "class/game/ageOfCube/map/unit/UnitController.h"
#include "class/game/ageOfCube/map/attack/AttackCreator.h"
namespace AOC {

Weapon::Weapon() {
	attack_timer=0;
	attack_cycle=300;
	attack_range=10;
	attack_damage=10;
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
		if(target&&(target->get_pos()-unit->get_attack_pos()).get_length()<=attack_range){
			fire(target);
			attack_success=true;
		}
	}
	return attack_success;
}
void Weapon::fire(Unit* target){
	if(!target)return;
	//std::cout<<"Ball::attack(Unit* target)"<<std::endl;
	Attack* attack=AttackCreator::get_cur_object()->create(get_attack_type());
	attack->radius=0.5*unit->get_attack_size();

	attack->pos=unit->get_attack_pos();
	attack->set_target(target);
	attack->set_damage(attack_damage*unit->get_atk_ajusted());
	attack->set_player(unit->get_player());
	attack->create_attack();
}
void Weapon::update(){
	if(!unit){
		std::cerr<<"Weapon::update() no unit set!!"<<std::endl;
		return;
	}

	attack_timer++;
	if(attack_timer>attack_cycle){
		if(attack()){
			attack_timer=0;
		}else{//attack false
			attack_timer*=0.8;
		}
	}
	weapon_update();
}
void Weapon::draw(){
	if(!unit)return;
	draw_weapon();
}
} /* namespace AOC */
