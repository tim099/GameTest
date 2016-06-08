#ifndef SOURCE_CLASS_GAME_AGEOFCUBE_MAP_MINION_MINIONCREATOR_H_
#define SOURCE_CLASS_GAME_AGEOFCUBE_MAP_MINION_MINIONCREATOR_H_
#include "class/game/ageOfCube/map/minion/Minion.h"
#include "class/tim/map/MapContainer.h"
#include "class/tim/globalObject/Singleton.h"
#include "class/tim/globalObject/GlobalObject.h"
namespace AOC {

class MinionCreator :public Tim::GlobalObject<MinionCreator> {
public:
	MinionCreator();
	virtual ~MinionCreator();
	Minion* create(std::string type_name);
protected:
	void push(Minion* obj);
	Tim::MapContainer<std::string,Minion>creator;
};

} /* namespace AOC */

#endif /* SOURCE_CLASS_GAME_AGEOFCUBE_MAP_MINION_MINIONCREATOR_H_ */
