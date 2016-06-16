#ifndef SOURCE_CLASS_GAME_AGEOFCUBE_UNIT_UNIT_H_
#define SOURCE_CLASS_GAME_AGEOFCUBE_UNIT_UNIT_H_

#include <string>
#include "class/tim/math/vec3.h"
#include "class/game/entity/Entity.h"
#include "class/game/ageOfCube/map/attack/weapon/Weapon.h"
#include "class/game/ageOfCube/player/resource/ResourceModifier.h"
#include "class/tim/map/MapContainer.h"

namespace AOC {

class Unit : public entity::Entity{//
	//friend Weapon;
public:
	Unit(int _max_hp=1);
	void init(int max_hp,int player);
	virtual ~Unit();
	virtual std::string get_name()const{return "Unit";}

	void create_unit();//create this unit will push it into UnitController

	inline bool get_is_dead()const{return is_dead;}
	inline bool get_terminate()const{return terminate;}
	inline int get_hp()const{return hp;}
	inline void set_max_hp(int _max_hp){max_hp=_max_hp;hp=max_hp;}
	inline void set_hp(int _hp){
		hp=_hp;
		if(hp<=0){
			is_dead=true;
			killed();
		}
	}
	inline void hp_alter(int amount){set_hp(hp+amount);}
	//inline void attack_alter(int amount){attack_damage += amount;}

	inline void max_hp_alter(int amount){max_hp += amount;hp=max_hp;}

	inline void set_attack_cycle(int _attack_cycle){
		attack_cycle=_attack_cycle;
		for(unsigned i=0;i<weapons.size();i++){
			weapons.at(i)->set_attack_cycle(attack_cycle);
		}
	}
	inline void attack_cycle_alter(int amount){
		if(attack_cycle+amount > 0){
			attack_cycle += amount;
			for(unsigned i=0;i<weapons.size();i++){
				weapons.at(i)->set_attack_cycle(attack_cycle);
			}
		}
	}
	inline void armor_alter(int amount){armor += amount;}
	void upgrade(std::string upgrade_name, int amount);

	inline int get_max_hp()const{return max_hp;}
	//inline int get_atk(){return attack_damage;}
	double get_atk_ajusted();
	inline int get_armor(){return armor;}
	int get_upgrade_amount(std::string upgrade_name);

	inline unsigned get_player()const{return player;}
	inline void set_player(unsigned _player){player=_player;}

	virtual math::vec3<double> get_rotate()=0;
	virtual math::vec3<double> get_pos()=0;
	virtual math::vec3<int> get_pos_int()=0;
	virtual math::vec3<double> get_mid_pos(){return get_pos();}
	virtual math::vec3<int> get_mid_pos_int(){return get_pos_int();}
	virtual math::vec3<double>get_size()=0;
	void save_unit(FILE * file);
	void load_unit(FILE * file);
	void update();
	void draw_unit();
protected:
	virtual void unit_create(){}
	virtual void unit_update(){}
	virtual void killed(){}
	void save_weapons(FILE* file);
	void load_weapons(FILE* file);
	void save_upgrades(FILE* file);
	void load_upgrades(FILE* file);
	void push_weapon(Weapon* weapon){
		weapon->set_unit(this);
		weapon->set_attack_cycle(attack_cycle);
		weapons.push_back(weapon);
	}
	std::vector<Weapon*> weapons;
	Tim::MapContainer<std::string,ResourceModifier> upgrades;
	int max_hp;
	int hp;
	int armor;

	unsigned player;
	int dead_timer;

	bool terminate;
	int is_dead;
	bool created;

	//int attack_damage;
private:
	int attack_cycle;
};

} /* namespace AOC */

#endif /* SOURCE_CLASS_GAME_AGEOFCUBE_UNIT_UNIT_H_ */
