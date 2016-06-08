#include "class/game/entity/Entity.h"
#include "class/game/entity/EntityController.h"
#include <iostream>
namespace entity{
Entity::Entity() {
	//std::cout<<"Entity::Entity()="<<this<<std::endl;
	id=0;
}
Entity::~Entity() {
	//std::cout<<"Entity::~Entity()="<<this<<std::endl;
	if(id)EntityController::get_cur_object()->remove_entity(this);
}
void Entity::create_entity(){
	EntityController::get_cur_object()->push_entity(this);
	//for(unsigned i=0;i<components.size();i++){
		//components.at(i)->id=id;
	//}
}
void Entity::save_entity(FILE* file){
	fprintf(file,"%u\n",id);
}
void Entity::load_entity(FILE* file){
	fscanf(file,"%u\n",&id);
}
}
