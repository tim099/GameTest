#include "class/game/ageOfCube/map/attack/AttackController.h"
#include "class/game/ageOfCube/map/attack/AttackCreator.h"
namespace AOC {

AttackController::AttackController() {
	weapon_creator=new WeaponCreator();
	creator=new AttackCreator();
	register_cur();
}
AttackController::~AttackController() {
	for(unsigned i=0;i<attacks.size();i++){
		delete attacks.at(i);
	}
	delete creator;
	delete weapon_creator;
}
void AttackController::update(){
	std::vector<Attack*>die_attacks;
	for(unsigned i=0;i<attacks.size();i++){
		if(attacks.at(i)->get_die()){
			die_attacks.push_back(attacks.at(i));
		}
		attacks.at(i)->update();
	}
	for(unsigned i=0;i<die_attacks.size();i++){
		delete die_attacks.at(i);
	}
}
void AttackController::draw(){
	for(unsigned i=0;i<attacks.size();i++){
		attacks.at(i)->draw();
	}
}
void AttackController::save(FILE *file){
	fprintf(file,"%u\n",attacks.size());
	Attack* attack;
	for(unsigned i=0;i<attacks.size();i++){
		attack=attacks.at(i);
		fprintf(file,"%s\n",attack->get_name().c_str());
		attack->save(file);

	}
}
void AttackController::load(FILE *file){
	///*
	unsigned attacks_size;
	char name[100];
	fscanf(file,"%u\n",&attacks_size);
	Attack* attack;
	for(unsigned i=0;i<attacks_size;i++){
		fscanf(file,"%s\n",name);
		attack=creator->create(name);
		attack->load(file);
		attack->create_attack();
	}
	//*/
}
} /* namespace AOC */
