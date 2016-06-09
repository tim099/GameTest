/*
 * Resource.cpp
 *
 *  Created on: 2016¦~6¤ë9¤é
 *      Author: LukeWu
 */

#include <class/game/ageOfCube/player/resource/Resource.h>

namespace AOC {

Resource::Resource() {
	amount = 0;
	description = "this is description";
}

Resource::~Resource() {
	// TODO Auto-generated destructor stub
}

void Resource::modifyAmount(int modifier){
	amount += modifier;
}

} /* namespace AOC */
