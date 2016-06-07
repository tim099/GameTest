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
Entity* EntityController::get_entity(int id){
		if(map.find(id)!=map.end()){
			return map[id];
		}else{
			std::cerr<<"EntityController::get_entity id:"<<id<<"false,id not exist"<<std::endl;
			return 0;
		}

}
void EntityController::push_entity(Entity* entity){
	if(!entity->id)entity->id=gen_id();
	map[entity->id]=entity;
}
void EntityController::remove_entity(Entity* entity){
	delete_id(entity->id);
	map.erase(entity->id);
}
int EntityController::gen_id(){
	if(avaliable_id.empty()){
		return ++id_num;
	}else{
		int id=avaliable_id.back();
		avaliable_id.pop_back();
		return id;
	}
}
void EntityController::delete_id(int id){
	if(id){
		avaliable_id.push_back(id);
	}
}
}
