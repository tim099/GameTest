#include "class/game/GamePlayer.h"
#include "class/game/Game.h"
namespace game {

GamePlayer::GamePlayer() {

}
GamePlayer::~GamePlayer() {

}
void GamePlayer::play(Game* game){
	bool restart;
	do{
		game->initialize();
		game->mainloop();
		restart=game->restart;
	}while(restart);

	delete game;
}
} /* namespace game */
