#ifndef SOURCE_CLASS_GAME_CONTROLLER_ENTITY_H_
#define SOURCE_CLASS_GAME_CONTROLLER_ENTITY_H_
#include <cstdio>
#include <vector>
#include "class/game/entity/Component.h"
namespace entity{
class Entity {
public:
	Entity();
	virtual ~Entity();
	void create_entity();
	void save_entity(FILE* file);
	void load_entity(FILE* file);
	inline void set_id(unsigned _id){
		id=_id;
		for(unsigned i=0;i<components.size();i++){
			components.at(i)->id=id;
		}
	}
	inline unsigned get_id()const{
		return id;
	}
	///*
	void push_component(Component* component){
		components.push_back(component);
		component->id=id;
	}
	//*/
private:
	unsigned id;
	//int test;
	std::vector<Component*>components;
};
}
#endif /* SOURCE_CLASS_GAME_CONTROLLER_ENTITY_H_ */
