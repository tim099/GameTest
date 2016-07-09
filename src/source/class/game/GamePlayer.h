#ifndef SOURCE_CLASS_GAME_GAMEPLAYER_H_
#define SOURCE_CLASS_GAME_GAMEPLAYER_H_
class Game;
namespace game {

class GamePlayer {
public:
	GamePlayer();
	virtual ~GamePlayer();
	void play(Game* game);
};

} /* namespace game */

#endif /* SOURCE_CLASS_GAME_GAMEPLAYER_H_ */
