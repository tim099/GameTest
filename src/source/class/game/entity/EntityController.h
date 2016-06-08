#ifndef SOURCE_CLASS_CONTROLLER_ENTITYCONTROLLER_H_
#define SOURCE_CLASS_CONTROLLER_ENTITYCONTROLLER_H_

#include "class/controller/Controller.h"
#include "class/tim/globalObject/GlobalObject.h"
#include "class/game/entity/Entity.h"
#include <vector>
namespace entity{
class EntityController: public Controller ,public Tim::GlobalObject<EntityController>{
public:
	EntityController();
	virtual ~EntityController();
	Entity* get_entity(unsigned id);
	void push_entity(Entity* entity);
	void remove_entity(Entity* entity);
	void delete_id(unsigned id);
	void save(FILE* file);
	void load(FILE* file);
	unsigned gen_id();

protected:
	std::vector<unsigned> avaliable_id;
	std::vector<Entity*>entities;
	unsigned id_num;
};
}
#endif /* SOURCE_CLASS_CONTROLLER_ENTITYCONTROLLER_H_ */
