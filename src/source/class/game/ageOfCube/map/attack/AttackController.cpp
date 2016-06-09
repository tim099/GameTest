#include "class/game/ageOfCube/map/attack/AttackController.h"
#include "class/game/ageOfCube/map/attack/AttackCreator.h"
namespace AOC {

AttackController::AttackController() {

	creator=new AttackCreator();
	register_cur();
}
AttackController::~AttackController() {
	for(unsigned i=0;i<attacks.size();i++){
		delete attacks.at(i);
	}
	delete creator;
}
void AttackController::update(){
	for(unsigned i=0;i<attacks.size();i++){
		attacks.at(i)->update();
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
