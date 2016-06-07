#ifndef SOURCE_CLASS_CONTROLLER_ENTITYCONTROLLER_H_
#define SOURCE_CLASS_CONTROLLER_ENTITYCONTROLLER_H_

#include "class/controller/Controller.h"
#include "class/tim/globalObject/GlobalObject.h"
#include "class/game/entity/Entity.h"
#include <vector>
#include <map>
namespace entity{
class EntityController: public Controller ,public Tim::GlobalObject<EntityController>{
public:
	EntityController();
	virtual ~EntityController();
	Entity* get_entity(int id);
	void push_entity(Entity* entity);
	void remove_entity(Entity* entity);
	void delete_id(int id);
	void save(FILE* file);
	void load(FILE* file);
	int gen_id();

protected:



	std::map<int,Entity*> map;
	std::vector<int> avaliable_id;
	unsigned id_num;
};
}
#endif /* SOURCE_CLASS_CONTROLLER_ENTITYCONTROLLER_H_ */
