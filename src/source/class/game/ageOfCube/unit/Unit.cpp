#include "class/game/ageOfCube/unit/Unit.h"
#include <cstdio>
namespace AOC {

Unit::Unit(int _max_hp) {
	init(_max_hp,0);
}
Unit::~Unit() {

}
void Unit::init(int _max_hp,int _player){
	max_hp = _max_hp;
	hp = max_hp;
	is_dead = false;
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
