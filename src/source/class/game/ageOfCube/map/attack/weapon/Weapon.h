#ifndef SOURCE_CLASS_GAME_AGEOFCUBE_MAP_ATTACK_WEAPON_WEAPON_H_
#define SOURCE_CLASS_GAME_AGEOFCUBE_MAP_ATTACK_WEAPON_WEAPON_H_
#include <cstdio>
#include <string>
namespace AOC {
class Unit;
class Weapon {
public:
	Weapon();
	virtual ~Weapon();
	void save(FILE* file);
	void load(FILE* file);
	void update();
	void set_unit(Unit* _unit){unit=_unit;}
	//void set_attack_type(const std::string &_attack_type){attack_type=_attack_type;}
protected:
	virtual void weapon_update(){}
	virtual bool attack();
	virtual void fire(Unit* target);
	int attack_timer,attack_cycle;
	//std::string attack_type;
	Unit* unit;
};

} /* namespace AOC */

#endif /* SOURCE_CLASS_GAME_AGEOFCUBE_MAP_ATTACK_WEAPON_WEAPON_H_ */
