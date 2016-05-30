#ifndef SOURCE_CLASS_GAME_AGEOFCUBE_MAP_MAPRIGIDBODY_H_
#define SOURCE_CLASS_GAME_AGEOFCUBE_MAP_MAPRIGIDBODY_H_

#include "class/physic/RigidBody.h"

namespace AOC {
class Map;
class MapRigidBody: public physic::RigidBody {
public:
	MapRigidBody(Map *map);
	virtual ~MapRigidBody();
	virtual std::string get_type()const{
		return "MapRigidBody";
	}
	virtual bool check_collision(physic::RigidBody* b);
	virtual void collide(RigidBody* b);
protected:
	bool check_stuck(physic::RigidBody* b);
	bool handle_stuck(physic::RigidBody* b);
	Map *map;
};

} /* namespace physic */

#endif /* SOURCE_CLASS_GAME_AGEOFCUBE_MAP_MAPRIGIDBODY_H_ */
