#ifndef SOURCE_CLASS_GAME_AGEOFCUBE_UNIT_UNIT_H_
#define SOURCE_CLASS_GAME_AGEOFCUBE_UNIT_UNIT_H_

#include <string>
#include "class/tim/math/vec3.h"
#include "class/game/entity/Entity.h"
namespace AOC {

class Unit : public entity::Entity{//
public:
	Unit(int _max_hp=1);
	void init(int max_hp,int player);
	virtual ~Unit();
	virtual std::string get_name()const{
		return "Unit";
	}
	void create_unit();//create this unit will push it into UnitController
	inline bool get_is_dead()const{return is_dead;}
	inline bool get_terminate()const{return terminate;}
	inline int get_hp()const{return hp;}
	inline void set_hp(int _hp){hp=_hp;if(hp<=0)is_dead=true;}
	inline void hp_alter(int amount){set_hp(hp+amount);}

	inline int get_max_hp()const{return max_hp;}
	inline int get_player()const{return player;}
	inline void set_player(int _player){player=_player;}

	virtual math::vec3<double> get_pos()=0;
	virtual math::vec3<int> get_pos_int()=0;
	virtual math::vec3<int> get_mid_pos_int();
	void save_unit(FILE * file);
	void load_unit(FILE * file);
	void update();
protected:
	virtual void unit_update(){}
	int max_hp;
	int hp;
	int player;
	int dead_timer;
	bool terminate;
	int is_dead;
	bool created;
};

} /* namespace AOC */

#endif /* SOURCE_CLASS_GAME_AGEOFCUBE_UNIT_UNIT_H_ */