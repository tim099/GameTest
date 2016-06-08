#ifndef SOURCE_CLASS_GAME_AGEOFCUBE_MAP_ATTACK_ATTACKCREATOR_H_
#define SOURCE_CLASS_GAME_AGEOFCUBE_MAP_ATTACK_ATTACKCREATOR_H_
#include "class/game/ageOfCube/map/attack/Attack.h"
#include "class/tim/map/MapContainer.h"
#include "class/tim/globalObject/GlobalObject.h"
namespace AOC {

class AttackCreator :public Tim::GlobalObject<AttackCreator>{
public:
	AttackCreator();
	virtual ~AttackCreator();
	Attack* create(std::string type_name);
protected:
	void push(Attack* obj);
	Tim::MapContainer<std::string,Attack>creator;
};

} /* namespace AOC */

#endif /* SOURCE_CLASS_GAME_AGEOFCUBE_MAP_ATTACK_ATTACKCREATOR_H_ */
