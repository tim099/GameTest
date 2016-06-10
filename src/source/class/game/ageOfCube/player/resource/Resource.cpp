/*
 * Resource.cpp
 *
 *  Created on: 2016�~6��9��
 *      Author: LukeWu
 */
#include <class/game/ageOfCube/player/resource/Resource.h>

namespace AOC {

Resource::Resource(std::string _name, std::string _description, int _amount) {
	name = _name;
	description = _description;
	amount = _amount;
}

Resource::~Resource() {
	// TODO Auto-generated destructor stub
}

void Resource::modifyAmount(int modifier){
	amount += modifier;
}

} /* namespace AOC */
