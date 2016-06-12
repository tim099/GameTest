#include "class/game/ageOfCube/map/unit/Unit.h"
#include "class/game/ageOfCube/map/unit/UnitController.h"
#include "class/game/ageOfCube/map/attack/AttackCreator.h"
#include <cstdio>
namespace AOC {

Unit::Unit(int _max_hp) {
	//std::cout<<"Unit::Unit(int _max_hp)="<<this<<std::endl;
	init(_max_hp,0);
}
Unit::~Unit() {
	//std::cout<<"Unit::~Unit()="<<this<<std::endl;
	if(created){
		UnitController::get_cur_object()->remove(this);
	}
	for(unsigned i=0;i<weapons.size();i++){
		delete weapons.at(i);
	}
}
void Unit::attack(Unit* target){
	if(!target)return;
	//std::cout<<"Ball::attack(Unit* target)"<<std::endl;
	Attack* attack=AttackCreator::get_cur_object()->create(get_attack_type());
	attack->radius=0.5*get_attack_size();

	attack->pos=get_attack_pos();
	attack->set_target(target);
	attack->set_damage(attack_damage);
	attack->create_attack();
}
void Unit::attack_update(){
	attack_timer++;
	if(attack_timer>attack_cycle){
		Unit* target;
		unsigned enemy_id=(get_player()==0?1:0);
		target=UnitController::get_cur_object()->search_unit(enemy_id,get_attack_pos());
		if(target&&(target->get_pos()-get_pos()).get_length()<get_attack_range()){
			attack(target);
			attack_timer=0;
		}else{
			attack_timer*=0.8;
		}
	}
}
math::vec3<int> Unit::get_mid_pos_int(){
	return get_pos_int();
}
void Unit::create_unit(){
	UnitController* controller=UnitController::get_cur_object();
	if(controller){
		controller->push(this);
	}else{
		std::cerr<<"Unit::create_unit() fail,no controller"<<std::endl;
	}
	create_entity();
	//std::cout<<"Unit::create_unit() id="<<id<<std::endl;
	created=true;
}
void Unit::init(int _max_hp,int _player){
	max_hp = _max_hp;
	hp = max_hp;
	armor = 0;
	is_dead = false;
	terminate=false;
	created=false;
	dead_timer=0;
	attack_damage=10;
	attack_timer=0;
	attack_cycle=300;
	set_player(_player);
}
void Unit::save_weapons(FILE* file){
	for(unsigned i=0;i<weapons.size();i++){
		weapons.at(i)->save(file);
	}
}
void Unit::load_weapons(FILE* file){
	for(unsigned i=0;i<weapons.size();i++){
		weapons.at(i)->load(file);
	}
}
void Unit::save_unit(FILE * file){
	fprintf(file,"%d %d %u %d %d %d\n",max_hp,hp,player,is_dead,dead_timer,attack_timer);
	fprintf(file,"%d %d\n",attack_damage,attack_cycle);
	//save_weapons(file);
	save_entity(file);
}
void Unit::load_unit(FILE * file){
	fscanf(file,"%d %d %u %d %d %d\n",&max_hp,&hp,&player,&is_dead,&dead_timer,&attack_timer);
	fscanf(file,"%d %d\n",&attack_damage,&attack_cycle);
	//load_weapons(file);
	load_entity(file);
}
void Unit::update(){
	if(is_dead){
		dead_timer++;
	}
	if(dead_timer>5){
		terminate=true;
	}

	if(is_dead)return;

	unit_update();
	for(unsigned i=0;i<weapons.size();i++){
		weapons.at(i)->update();
	}

}
} /* namespace AOC */
