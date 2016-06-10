/*
 * ResourceModifier.cpp
 *
 *  Created on: 2016¦~6¤ë10¤é
 *      Author: LukeWu
 */

#include <class/game/ageOfCube/player/resource/ResourceModifier.h>

namespace AOC {

ResourceModifier::ResourceModifier(std::string _name, int _amount) {
	resource_name = _name;
	amount = _amount;
}

ResourceModifier::~ResourceModifier() {
	// TODO Auto-generated destructor stub
}

} /* namespace AOC */
