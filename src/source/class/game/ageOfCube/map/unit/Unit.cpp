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
	attack_cycle=300;
	set_player(_player);
	upgrades.push("fire",new ResourceModifier("fire",0));
	upgrades.push("water",new ResourceModifier("water",0));
	upgrades.push("earth",new ResourceModifier("earth",0));
	upgrades.push("air",new ResourceModifier("air",0));
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
	fprintf(file,"%d %d %u %d %d\n",max_hp,hp,player,is_dead,dead_timer);
	fprintf(file,"%d %d\n",attack_damage,attack_cycle);
	save_weapons(file);
	save_entity(file);
}
void Unit::load_unit(FILE * file){
	fscanf(file,"%d %d %u %d %d\n",&max_hp,&hp,&player,&is_dead,&dead_timer);
	fscanf(file,"%d %d\n",&attack_damage,&attack_cycle);
	load_weapons(file);
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

void Unit::upgrade(std::string upgrade_name, int amount){
	upgrades.get(upgrade_name)->amount_alter(amount);
}


int Unit::get_upgrade_amount(std::string upgrade_name){

	return upgrades.get(upgrade_name)->get_amount();
}

} /* namespace AOC */
