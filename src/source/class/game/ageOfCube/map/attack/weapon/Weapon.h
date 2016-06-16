#ifndef SOURCE_CLASS_GAME_AGEOFCUBE_MAP_ATTACK_WEAPON_WEAPON_H_
#define SOURCE_CLASS_GAME_AGEOFCUBE_MAP_ATTACK_WEAPON_WEAPON_H_
#include <cstdio>
#include <string>
#include "class/tim/math/vec3.h"
namespace AOC {
class Unit;
class Weapon {
public:
	virtual void weapon_pre_init(){}
	Weapon();
	virtual ~Weapon();
	virtual Weapon* clone()=0;
	virtual std::string get_name()=0;
	virtual std::string get_attack_type()=0;
	virtual math::vec3<double>get_attack_pos();
	virtual math::vec3<double>get_pos();
	void save(FILE* file);
	void load(FILE* file);
	void update();
	void draw();
	void set_unit(Unit* _unit){unit=_unit;}
	void set_attack_cycle(int _attack_cycle){attack_cycle=_attack_cycle;}
	void set_attack_range(double _attack_range){attack_range=_attack_range;}
	void set_attack_damage(double _damage){attack_damage=_damage;}
	void set_pos(const math::vec3<double>&_pos){pos=_pos;}
	void set_attack_size(double _attack_size){attack_size=_attack_size;}
protected:
	virtual void weapon_update(){}
	virtual void draw_weapon(){}
	virtual bool attack();
	virtual void fire(Unit* target);
	Unit* find_target(math::vec3<double> attack_pos);
	int attack_timer,attack_cycle;
	int attack_damage;
	double attack_range;
	double attack_size;
	math::vec3<double>pos;
	Unit* unit;
};

} /* namespace AOC */

#endif /* SOURCE_CLASS_GAME_AGEOFCUBE_MAP_ATTACK_WEAPON_WEAPON_H_ */
