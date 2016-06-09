#ifndef SOURCE_CLASS_GAME_ENTITY_ENTITYPOINTER_H_
#define SOURCE_CLASS_GAME_ENTITY_ENTITYPOINTER_H_

namespace entity {
class Entity;
class EntityPointer {
public:
	EntityPointer();
	virtual ~EntityPointer();
	unsigned get_id()const{return id;}
	Entity* get_entity()const;

	static Entity* get_entity(unsigned id);
protected:
	unsigned id;
};

} /* namespace entity */

#endif /* SOURCE_CLASS_GAME_ENTITY_ENTITYPOINTER_H_ */
