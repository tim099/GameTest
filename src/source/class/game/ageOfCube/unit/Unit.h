/*
 * Unit.h
 *
 *  Created on: 2016¦~5¤ë17¤é
 *      Author: LukeWu
 */

#ifndef SOURCE_CLASS_GAME_AGEOFCUBE_UNIT_UNIT_H_
#define SOURCE_CLASS_GAME_AGEOFCUBE_UNIT_UNIT_H_

#include <string>

namespace AOC {

class Unit {
public:
	Unit(int _max_hp=1);
	virtual ~Unit();
	virtual std::string get_name()const{
		return "Unit";
	}
	int get_hp(){return hp;}
	int get_max_hp(){return max_hp;}
protected:
	int max_hp;
	int hp;
	float speed;
	bool is_dead;
};

} /* namespace AOC */

#endif /* SOURCE_CLASS_GAME_AGEOFCUBE_UNIT_UNIT_H_ */
