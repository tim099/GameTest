#include "class/game/ageOfCube/unit/Unit.h"
#include "class/game/ageOfCube/unit/UnitController.h"
#include <cstdio>
namespace AOC {

Unit::Unit(int _max_hp) {
	init(_max_hp,0);
	//UnitController::get_cur_object()->push(this);
}
Unit::~Unit() {
	if(created){
		UnitController::get_cur_object()->remove(this);
	}
}
void Unit::push_to_controller(){
	UnitController::get_cur_object()->push(this);
	created=true;
}
void Unit::init(int _max_hp,int _player){
	max_hp = _max_hp;
	hp = max_hp;
	is_dead = false;
	created=false;
	set_player(_player);
}
void Unit::save_unit(FILE * file){
	fprintf(file,"%d %d %d %d\n",max_hp,hp,player,is_dead);
}
void Unit::load_unit(FILE * file){
	//fscanf(file,"%d %d %d\n",&max_hp,&hp,(int*)&is_dead);
	fscanf(file,"%d %d %d %d\n",&max_hp,&hp,&player,(int*)&is_dead);
}
} /* namespace AOC */
