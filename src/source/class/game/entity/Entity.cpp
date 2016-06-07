#include "class/game/entity/Entity.h"
#include "class/game/entity/EntityController.h"
namespace entity{
Entity::Entity() {
	id=0;
}
Entity::~Entity() {
	if(id)EntityController::get_cur_object()->remove_entity(this);
}
void Entity::create_entity(){
	EntityController::get_cur_object()->push_entity(this);
}
void Entity::save_entity(FILE* file){
	fprintf(file,"%d\n",id);
}
void Entity::load_entity(FILE* file){
	fscanf(file,"%d\n",&id);
}
}
