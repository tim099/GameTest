#include "class/game/ageOfCube/map/unit/Unit.h"
#include "class/game/ageOfCube/map/unit/UnitController.h"
#include "class/game/ageOfCube/map/attack/AttackCreator.h"
#include <cstdio>
namespace AOC {

Unit::Unit(int _max_hp) {
	//std::cout<<"Unit::Unit(int _max_hp)="<<this<<std::endl;
	upgrades.push("fire",new ResourceModifier("fire",0));
	upgrades.push("water",new ResourceModifier("water",0));
	upgrades.push("earth",new ResourceModifier("earth",0));
	upgrades.push("air",new ResourceModifier("air",0));

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
double Unit::get_atk_ajusted(){
	int amount=upgrades.get("fire")->get_amount();
	return 1.0+0.1*amount;
}
void Unit::create_unit(){
	UnitController* controller=UnitController::get_cur_object();
	if(controller){
		controller->push(this);
	}else{
		std::cerr<<"Unit::create_unit() fail,no controller"<<std::endl;
	}
	create_entity();
	unit_create();
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
	//attack_damage=10;
	attack_cycle=300;
	set_player(_player);
}
void Unit::save_weapons(FILE* file){
	fprintf(file,"%u\n",weapons.size());
	for(unsigned i=0;i<weapons.size();i++){
		weapons.at(i)->save(file);
	}
}
void Unit::load_weapons(FILE* file){
	unsigned weapons_size;
	fscanf(file,"%u\n",&weapons_size);
	for(unsigned i=0;i<weapons.size()&&i<weapons_size;i++){
		weapons.at(i)->load(file);
	}
}
void Unit::save_unit(FILE * file){
	fprintf(file,"%d %d %u %d %d\n",max_hp,hp,player,is_dead,dead_timer);
	fprintf(file,"%d\n",attack_cycle);
	save_weapons(file);
	save_upgrades(file);
	save_entity(file);
}
void Unit::load_unit(FILE * file){
	fscanf(file,"%d %d %u %d %d\n",&max_hp,&hp,&player,&is_dead,&dead_timer);
	fscanf(file,"%d\n",&attack_cycle);
	load_weapons(file);
	load_upgrades(file);
	load_entity(file);
}
void Unit::save_upgrades(FILE* file){
	fprintf(file,"%d %d %d %d\n",upgrades.get("fire")->get_amount(),
			upgrades.get("water")->get_amount(),
			upgrades.get("earth")->get_amount(),
			upgrades.get("air")->get_amount());

}
void Unit::load_upgrades(FILE* file){
	int fire,water,earth,air;
	fscanf(file,"%d %d %d %d\n",&fire,&water,&earth,&air);
	upgrades.get("fire")->set_amount(fire);
	upgrades.get("water")->set_amount(water);
	upgrades.get("earth")->set_amount(earth);
	upgrades.get("air")->set_amount(air);
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
void Unit::draw_unit(){
	if(is_dead)return;
	for(unsigned i=0;i<weapons.size();i++){
		weapons.at(i)->draw();
	}
}
void Unit::upgrade(std::string upgrade_name, int amount){
	upgrades.get(upgrade_name)->amount_alter(amount);
}


int Unit::get_upgrade_amount(std::string upgrade_name){

	return upgrades.get(upgrade_name)->get_amount();
}

} /* namespace AOC */
