/*
 * PlayerController.h
 *
 *  Created on: 2016¦~6¤ë10¤é
 *      Author: LukeWu
 */

#ifndef SOURCE_CLASS_GAME_AGEOFCUBE_PLAYER_PLAYERCONTROLLER_H_
#define SOURCE_CLASS_GAME_AGEOFCUBE_PLAYER_PLAYERCONTROLLER_H_

#include <vector>
#include "class/game/ageOfCube/player/Player.h"
#include "class/controller/Controller.h"
#include "class/display/UI/unitUI/BuildingUI.h"
#include "class/tim/globalObject/GlobalObject.h"
#include "class/input/signal/Receiver.h"
#include "class/display/UI/string/UIString.h"
#include "class/tim/pointer/SmartPointer.h"
#include <iostream>

namespace Display{
class Draw;
}

namespace AOC {

class PlayerController : public Controller ,public Tim::GlobalObject<PlayerController> {
public:
	PlayerController();
	virtual ~PlayerController();
	virtual void update();

	void draw(Display::Draw* draw);
	void push(Player* _player){
		players.push_back(_player);
	}
	void remove(Player* _player){
		for(unsigned i=0;i<players.size();i++){
			if(players.at(i)==_player){
				players.at(i)=players.back();
				players.pop_back();
			}
		}
	}
	Player* search_player(int player_id);
	void save(FILE *file);
	void load(FILE *file);
protected:
	void handle_signal();
	void save_player(FILE *file);
	void load_player(FILE *file);
	Player *current_player;
	std::vector<Player*>players;
	Input::Receiver* receiver;
};

} /* namespace AOC */

#endif /* SOURCE_CLASS_GAME_AGEOFCUBE_PLAYER_PLAYERCONTROLLER_H_ */
