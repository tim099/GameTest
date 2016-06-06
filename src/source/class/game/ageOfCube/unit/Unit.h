#ifndef SOURCE_CLASS_GAME_AGEOFCUBE_UNIT_UNIT_H_
#define SOURCE_CLASS_GAME_AGEOFCUBE_UNIT_UNIT_H_

#include <string>
#include "class/tim/math/vec3.h"
namespace AOC {

class Unit {
public:
	Unit(int _max_hp=1);
	void init(int max_hp,int player);
	virtual ~Unit();
	virtual std::string get_name()const{
		return "Unit";
	}
	void push_to_controller();//create this unit will push it into UnitController
	inline int get_hp()const{return hp;}
	inline int get_max_hp()const{return max_hp;}
	inline int get_player()const{return player;}
	inline void set_player(int _player){player=_player;}
	virtual math::vec3<double> get_pos()=0;
	virtual math::vec3<int> get_pos_int()=0;
	virtual math::vec3<int> get_mid_pos_int();
	void save_unit(FILE * file);
	void load_unit(FILE * file);
	virtual void unit_update(){

	}
protected:
	int max_hp;
	int hp;
	int player;
	int dead_timer;
	bool is_dead;
	bool created;
};

} /* namespace AOC */

#endif /* SOURCE_CLASS_GAME_AGEOFCUBE_UNIT_UNIT_H_ */
