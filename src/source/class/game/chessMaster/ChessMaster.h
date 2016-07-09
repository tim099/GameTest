#ifndef SOURCE_CLASS_GAME_CHESSMASTER_CHESSMASTER_H_
#define SOURCE_CLASS_GAME_CHESSMASTER_CHESSMASTER_H_
#include "class/game/Game.h"

#include "class/display/texture/AllTextures.h"
#include "class/display/draw/drawObject/AllDrawObjects.h"
#include "class/display/model/modelBuffer/AllModelBuffers.h"
#include "class/audio/AllAudioSources.h"
class ChessMaster : public Game{
public:
	ChessMaster();
	virtual ~ChessMaster();
protected:
	virtual std::string window_name(){
		return std::string("Chess Master");
	}
	virtual void initialize_game();
	virtual void terminate_game();
	virtual void game_update();

	Display::AllDrawObjects *drawObjects;
	Display::AllTextures* textures;
	Display::AllModelBuffers* modelBuffers;
	Audio::AllAudioSources *audioSources;
};

#endif /* SOURCE_CLASS_GAME_CHESSMASTER_CHESSMASTER_H_ */
