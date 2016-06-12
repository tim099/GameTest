/*
 * ResourceModifier.h
 *
 *  Created on: 2016¦~6¤ë10¤é
 *      Author: LukeWu
 */

#ifndef SOURCE_CLASS_GAME_AGEOFCUBE_PLAYER_RESOURCE_RESOURCEMODIFIER_H_
#define SOURCE_CLASS_GAME_AGEOFCUBE_PLAYER_RESOURCE_RESOURCEMODIFIER_H_

#include <string>

namespace AOC {

class ResourceModifier {
public:
	ResourceModifier(std::string _name="cube", int _amount=0);
	virtual ~ResourceModifier();
	std::string get_name(){return resource_name;}
	int get_amount(){return amount;}
private:
	std::string resource_name;
	int amount;
};

} /* namespace AOC */

#endif /* SOURCE_CLASS_GAME_AGEOFCUBE_PLAYER_RESOURCE_RESOURCEMODIFIER_H_ */
