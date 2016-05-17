/*
 * Unit.cpp
 *
 *  Created on: 2016¦~5¤ë17¤é
 *      Author: LukeWu
 */

#include "class/game/ageOfCube/unit/Unit.h"

namespace AOC {

Unit::Unit(int _max_hp) {
	// TODO Auto-generated constructor stub
	max_hp = _max_hp;
	hp = max_hp;
	speed = 0.0f;
	is_dead = false;
}

Unit::~Unit() {
	// TODO Auto-generated destructor stub
}

} /* namespace AOC */
