/*
 * Resource.h
 *
 *  Created on: 2016¦~6¤ë9¤é
 *      Author: LukeWu
 */

#ifndef SOURCE_CLASS_GAME_AGEOFCUBE_PLAYER_RESOURCE_RESOURCE_H_
#define SOURCE_CLASS_GAME_AGEOFCUBE_PLAYER_RESOURCE_RESOURCE_H_

#include <string>

namespace AOC {

class Resource {
public:
	Resource();
	virtual ~Resource();
	void modifyAmount(int modifier);
private:
	int amount;
	std::string description;
};

} /* namespace AOC */

#endif /* SOURCE_CLASS_GAME_AGEOFCUBE_PLAYER_RESOURCE_RESOURCE_H_ */
