#ifndef SOURCE_CLASS_GAME_AGEOFCUBE_UNIT_UNIT_H_
#define SOURCE_CLASS_GAME_AGEOFCUBE_UNIT_UNIT_H_

#include <string>

namespace AOC {

class Unit {
public:
	Unit(int _max_hp=1);
	void init(int max_hp,int player);
	virtual ~Unit();
	virtual std::string get_name()const{
		return "Unit";
	}
	inline int get_hp()const{return hp;}
	inline int get_max_hp()const{return max_hp;}
	inline int get_player_hp()const{return player;}
	inline void set_player(int _player){player=_player;}
	void save_unit(FILE * file);
	void load_unit(FILE * file);
	virtual void unit_update(){

	}
protected:
	int max_hp;
	int hp;
	int player;
	bool is_dead;
};

} /* namespace AOC */

#endif /* SOURCE_CLASS_GAME_AGEOFCUBE_UNIT_UNIT_H_ */
