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
	/*
	void push_component(Component* component){
		components.push_back(component);
		component->id=id;
	}
	*/

	unsigned id;
	//int test;
	std::vector<Component*>components;
};
}
#endif /* SOURCE_CLASS_GAME_CONTROLLER_ENTITY_H_ */
