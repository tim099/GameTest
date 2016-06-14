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
	Resource(std::string _name, std::string _description, int _amount=0);
	virtual ~Resource();
	bool modifyAmount(int modifier);
	std::string get_name(){return name;}
	int get_amount(){return amount;}
	void set_amount(int _amount){amount=_amount;}
private:
	int amount;
	std::string name;
	std::string description;
};

} /* namespace AOC */

#endif /* SOURCE_CLASS_GAME_AGEOFCUBE_PLAYER_RESOURCE_RESOURCE_H_ */
