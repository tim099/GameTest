#ifndef SOURCE_CLASS_GAME_AGEOFCUBE_MAP_ATTACK_WEAPON_WEAPON_H_
#define SOURCE_CLASS_GAME_AGEOFCUBE_MAP_ATTACK_WEAPON_WEAPON_H_
#include <cstdio>
#include <string>
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

	void save(FILE* file);
	void load(FILE* file);
	void update();
	void draw();
	void set_unit(Unit* _unit){unit=_unit;}
	void set_attack_cycle(int _attack_cycle){attack_cycle=_attack_cycle;}
	void set_attack_range(double _attack_range){attack_range=_attack_range;}
protected:
	virtual void weapon_update(){}
	virtual void draw_weapon(){}
	virtual bool attack();
	virtual void fire(Unit* target);
	int attack_timer,attack_cycle;
	double attack_range;
	Unit* unit;
};

} /* namespace AOC */

#endif /* SOURCE_CLASS_GAME_AGEOFCUBE_MAP_ATTACK_WEAPON_WEAPON_H_ */
