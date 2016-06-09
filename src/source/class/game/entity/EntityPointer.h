#ifndef SOURCE_CLASS_GAME_ENTITY_ENTITYPOINTER_H_
#define SOURCE_CLASS_GAME_ENTITY_ENTITYPOINTER_H_

namespace entity {
class Entity;
class EntityPointer {
public:
	EntityPointer();
	virtual ~EntityPointer();
	void update();
	unsigned get_id()const{return id;}
	Entity* get_entity()const{return entity;}
protected:
	Entity* entity;
	unsigned id;
};

} /* namespace entity */

#endif /* SOURCE_CLASS_GAME_ENTITY_ENTITYPOINTER_H_ */
