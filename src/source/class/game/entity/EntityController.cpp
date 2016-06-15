#include "class/game/entity/EntityController.h"
#include <iostream>
namespace entity{
EntityController::EntityController() {
	id_num=0;
	register_cur();
}
EntityController::~EntityController() {

}
void EntityController::save(FILE* file){
	fprintf(file,"%u\n",id_num);
	fprintf(file,"%u\n",avaliable_id.size());
	for(unsigned i=0;i<avaliable_id.size();i++){
		fprintf(file,"%d\n",avaliable_id.at(i));
	}
}
void EntityController::load(FILE* file){
	fscanf(file,"%u\n",&id_num);
	unsigned avaliable_id_size;
	fscanf(file,"%u\n",&avaliable_id_size);
	int id;
	for(unsigned i=0;i<avaliable_id_size;i++){
		fscanf(file,"%d\n",&id);
		avaliable_id.push_back(id);
	}
}
Entity* EntityController::get_entity(unsigned id){
	if(id<entities.size()){
		return entities.at(id);
	}else{
		std::cerr<<"EntityController::get_entity(int id) id="<<id<<"out if range"<<std::endl;
		return 0;
	}
}
void EntityController::push_entity(Entity* entity){
	//std::cout<<"EntityController::push_entity="<<entity<<std::endl;
	if(!entity->get_id()){
		entity->set_id(gen_id());
	}
	if(entity->get_id()>=entities.size()){
		entities.resize(entities.size()+entity->get_id()+1,0);
		std::cout<<"EntityController::push_entity resize:"<<entities.size()<<std::endl;
	}
	entities.at(entity->get_id())=entity;
}
void EntityController::remove_entity(Entity* entity){
	delete_id(entity->get_id());
	if(entity->get_id()<entities.size()){
		//std::cout<<"EntityController::remove_entity id="<<entity->id<<std::endl;
		//std::cout<<"EntityController::remove_entity size="<<entities.size()<<std::endl;
		entities.at(entity->get_id())=0;
	}else{
		std::cerr<<"EntityController::remove_entity(Entity* entity)"<<entity->get_id()
				<<"out if range"<<std::endl;
	}

}
unsigned EntityController::gen_id(){
	if(avaliable_id.empty()){
		return ++id_num;
	}else{
		int id=avaliable_id.back();
		avaliable_id.pop_back();
		return id;
	}
}
void EntityController::delete_id(unsigned id){
	if(id){
		avaliable_id.push_back(id);
	}
}
}
