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
	is_dead = false;
	terminate=false;
	created=false;
	dead_timer=0;
	attack_damage=10;
	attack_timer=0;
	attack_cycle=300;
	set_player(_player);
}
void Unit::save_unit(FILE * file){
	fprintf(file,"%d %d %u %d %d %d\n",max_hp,hp,player,is_dead,dead_timer,attack_timer);
	save_entity(file);
}
void Unit::load_unit(FILE * file){
	fscanf(file,"%d %d %u %d %d %d\n",&max_hp,&hp,&player,&is_dead,&dead_timer,&attack_timer);
	load_entity(file);
}
void Unit::update(){
	if(is_dead){
		dead_timer++;
	}
	if(dead_timer>5){
		terminate=true;
	}
	if(!terminate){
		unit_update();
	}
}
} /* namespace AOC */
