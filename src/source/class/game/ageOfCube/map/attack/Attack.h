#ifndef SOURCE_CLASS_GAME_AGEOFCUBE_MAP_ATTACK_ATTACK_H_
#define SOURCE_CLASS_GAME_AGEOFCUBE_MAP_ATTACK_ATTACK_H_

#include "class/physic/RigidBody.h"
namespace Display{
	class DrawObject;
}
namespace AOC {
class Unit;
class Attack : public physic::RigidBody{
public:
	virtual void attack_pre_init(){}
	Attack();
	virtual ~Attack();
	virtual Attack* clone()=0;
	virtual std::string get_name()=0;
	void set_target(Unit* _target){target=_target;}
	void draw();
	void update();
	void create_attack();
protected:
	virtual void draw_attack()=0;
	virtual void attack_update()=0;
	Unit* target;
private:
	bool attack_created;
};

} /* namespace AOC */

#endif /* SOURCE_CLASS_GAME_AGEOFCUBE_MAP_ATTACK_ATTACK_H_ */
