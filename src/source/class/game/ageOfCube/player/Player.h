#ifndef SOURCE_CLASS_GAME_AGEOFCUBE_PLAYER_PLAYER_H_
#define SOURCE_CLASS_GAME_AGEOFCUBE_PLAYER_PLAYER_H_

#include <vector>
#include "class/game/ageOfCube/player/playerUI/PlayerUI.h"
#include "class/game/ageOfCube/player/resource/Resource.h"
#include "class/game/ageOfCube/player/resource/ResourceModifier.h"
#include "class/tim/map/MapContainer.h"

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
	int get_score(){return score;}
	void score_alter(int amount){set_score(score+amount);}
	void set_score(int _score);
	void modify_score(int amount){score += amount;}
	void init_UI();
	bool modify_resource(ResourceModifier modifier);
	bool modify_resource(std::string resource_name, int requested_amount);

	void save(FILE *file);
	void load(FILE *file);
private:
	unsigned int id;
	int score;
	std::string name;
	PlayerType type;
	UI::PlayerUI *player_UI;
	Tim::MapContainer<std::string,Resource> resources;
};

} /* namespace AOC */

#endif /* SOURCE_CLASS_GAME_AGEOFCUBE_PLAYER_PLAYER_H_ */
