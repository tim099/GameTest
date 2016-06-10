#ifndef SOURCE_CLASS_GAME_AGEOFCUBE_PLAYER_PLAYER_H_
#define SOURCE_CLASS_GAME_AGEOFCUBE_PLAYER_PLAYER_H_

#include <vector>
#include "class/display/UI/playerUI/PlayerUI.h"
#include "class/game/ageOfCube/player/resource/Resource.h"
#include "class/game/ageOfCube/player/resource/ResourceModifier.h"

namespace Display{
class Draw;
}

namespace AOC {

enum PlayerType{type_player,type_bot,type_observer,type_none};

class Player {
public:
	Player(int _id=0, PlayerType _type=type_none);
	virtual ~Player();
	void draw(Display::Draw* draw);
	void update();
	unsigned int get_id(){return id;}
	void init_UI();
	bool modify_resource(ResourceModifier modifier);
private:
	unsigned int id;
	std::string name;
	PlayerType type;
	std::vector<Resource> resources;
	UI::PlayerUI *player_UI;
};

} /* namespace AOC */

#endif /* SOURCE_CLASS_GAME_AGEOFCUBE_PLAYER_PLAYER_H_ */
