#ifndef SOURCE_CLASS_GAME_CONTROLLER_ENTITY_H_
#define SOURCE_CLASS_GAME_CONTROLLER_ENTITY_H_
#include <cstdio>
namespace entity{
class Entity {
public:
	Entity();
	virtual ~Entity();
	void create_entity();
	void save_entity(FILE* file);
	void load_entity(FILE* file);
	int id;
};
}
#endif /* SOURCE_CLASS_GAME_CONTROLLER_ENTITY_H_ */
