#ifndef SOURCE_CLASS_GAME_AGEOFCUBE_MAP_ATTACK_ATTACK_H_
#define SOURCE_CLASS_GAME_AGEOFCUBE_MAP_ATTACK_ATTACK_H_

#include "class/physic/RigidBody.h"
#include <vector>
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
	void create_attack();
	virtual Attack* clone()=0;
	virtual std::string get_name()=0;
	int get_die()const{return die;}
	void save(FILE* file);
	void load(FILE* file);
	void set_target(Unit* _target);
	void set_damage(int _damage){damage=_damage;}
	void set_player(unsigned _player){player_id=_player;}
	void draw();
	void update();
protected:
	virtual void save_attack(FILE* file){}
	virtual void load_attack(FILE* file){}
	virtual void draw_attack()=0;
	virtual void attack_update()=0;
	void damage_target(int amount);
	Unit* target;
	std::vector<Unit*> collied_units;
	unsigned target_id;
	unsigned player_id;
	int die;
	int damage;
private:

	int attack_created;
};

} /* namespace AOC */

#endif /* SOURCE_CLASS_GAME_AGEOFCUBE_MAP_ATTACK_ATTACK_H_ */
