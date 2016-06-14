#include "class/game/ageOfCube/map/attack/Attack.h"
#include "class/game/ageOfCube/map/attack/AttackController.h"
#include "class/game/ageOfCube/map/Map.h"
#include "class/game/ageOfCube/map/DisplayMap.h"
#include "class/game/ageOfCube/map/unit/Unit.h"
#include "class/game/entity/EntityPointer.h"
#include "class/game/ageOfCube/map/unit/UnitController.h"
#include "class/game/ageOfCube/player/PlayerController.h"
namespace AOC {

Attack::Attack() {
	die=false;
	target=0;
	target_id=0;
	attack_created=false;
	damage=10;
	player_id=0;
}
Attack::~Attack() {
	if(attack_created){
		AttackController::get_cur_object()->remove(this);
	}
}
void Attack::save(FILE* file){
	fprintf(file,"%u %d %d %u\n",target_id,die,damage,player_id);
	save_rigid_body(file);
	save_attack(file);
}
void Attack::load(FILE* file){
	fscanf(file,"%u %d %d %u\n",&target_id,&die,&damage,&player_id);
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
void Attack::damage_target(int amount){
	//std::cout<<"Attack::damage_target"<<std::endl;
	target->hp_alter(-amount);
	if(target->get_is_dead()){
		Player* player=PlayerController::get_cur_object()->search_player(player_id);
		player->score_alter(target->get_max_hp());
	}
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
		target=UnitController::get_cur_object()->search_unit(target->get_player(),pos);//"MainTower"
	}
	collied_units.clear();
	for(unsigned i=0;i<be_collided_id.size();i++){
		entity::Entity* entity=entity::EntityPointer::get_entity(be_collided_id.at(i));
		if(Unit* unit=dynamic_cast<Unit*>(entity)){
			collied_units.push_back(unit);
		}
	}
	for(unsigned i=0;i<collided_id.size();i++){
		entity::Entity* entity=entity::EntityPointer::get_entity(collided_id.at(i));
		if(Unit* unit=dynamic_cast<Unit*>(entity)){
			collied_units.push_back(unit);
		}
	}
	attack_update();
}
void Attack::draw(){
	if(die)return;
	math::vec3<double> s=Map::get_cur_object()->dp_map->dp_start;
	math::vec3<double> e=Map::get_cur_object()->dp_map->dp_end;
	if(pos>=s&&pos<=e){
		draw_attack();
	}
}
} /* namespace AOC */
