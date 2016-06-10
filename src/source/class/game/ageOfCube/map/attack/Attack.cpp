#include "class/game/ageOfCube/map/attack/Attack.h"
#include "class/game/ageOfCube/map/attack/AttackController.h"
#include "class/game/ageOfCube/map/Map.h"
#include "class/game/ageOfCube/map/DisplayMap.h"
#include "class/game/ageOfCube/map/unit/Unit.h"
#include "class/game/entity/EntityPointer.h"
namespace AOC {

Attack::Attack() {
	die=false;
	target=0;
	target_id=0;
	attack_created=false;
	damage=10;
}
Attack::~Attack() {
	if(attack_created){
		AttackController::get_cur_object()->remove(this);
	}
}
void Attack::save(FILE* file){
	fprintf(file,"%u %d %d\n",target_id,die,damage);
	save_rigid_body(file);
	save_attack(file);
}
void Attack::load(FILE* file){
	fscanf(file,"%u %d %d\n",&target_id,&die,&damage);
	std::cout<<"Attack::load target_id="<<target_id<<std::endl;
	load_rigid_body(file);
	load_attack(file);
}
void Attack::create_attack(){
	attack_created=true;
	AttackController::get_cur_object()->push(this);
}
void Attack::set_target(Unit* _target){
	target=_target;target_id=target->get_id();
}
void Attack::update(){
	if(die)return;

	set_detect_collision();
	if(target_id){
		//std::cout<<"Attack::update() target_id="<<target_id<<std::endl;
		if(!target){
			entity::Entity* entity=entity::EntityPointer::get_entity(target_id);
			target=dynamic_cast<Unit*>(entity);
			if(!target){
				//std::cout<<"Attack::update() target_id fail no target="<<target_id<<std::endl;
				target_id=0;
			}
		}
	}
	if(target&&target->get_is_dead()){
		target=0;
	}
	collied_units.clear();
	if(be_collided_id){
		entity::Entity* entity=entity::EntityPointer::get_entity(be_collided_id);
		if(Unit* unit=dynamic_cast<Unit*>(entity)){
			collied_units.push_back(unit);
		}
	}
	if(collided_id){
		entity::Entity* entity=entity::EntityPointer::get_entity(collided_id);
		if(Unit* unit=dynamic_cast<Unit*>(entity)){
			collied_units.push_back(unit);
		}
	}
	attack_update();
}
void Attack::draw(){
	math::vec3<double> s=Map::get_cur_object()->dp_map->dp_start;
	math::vec3<double> e=Map::get_cur_object()->dp_map->dp_end;
	if(pos>=s&&pos<=e){
		draw_attack();
	}
}
} /* namespace AOC */
