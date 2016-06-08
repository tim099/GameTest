#ifndef SOURCE_CLASS_GAME_AGEOFCUBE_MAP_ATTACK_ATTACK_H_
#define SOURCE_CLASS_GAME_AGEOFCUBE_MAP_ATTACK_ATTACK_H_

#include "class/physic/RigidBody.h"

namespace AOC {

class Attack{
public:
	Attack();
	virtual ~Attack();
	virtual void attack_pre_init(){}
	virtual Attack* clone()=0;
	virtual std::string get_name()=0;
	void create_attack();
protected:

private:
	physic::RigidBody rigid_body;
	bool attack_created;
};

} /* namespace AOC */

#endif /* SOURCE_CLASS_GAME_AGEOFCUBE_MAP_ATTACK_ATTACK_H_ */
