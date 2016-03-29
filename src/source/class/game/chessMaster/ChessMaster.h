#ifndef SOURCE_CLASS_GAME_CHESSMASTER_CHESSMASTER_H_
#define SOURCE_CLASS_GAME_CHESSMASTER_CHESSMASTER_H_
#include "class/game/Game.h"

#include "class/display/texture/AllTextures.h"
#include "class/display/draw/drawObject/AllDrawObjects.h"
#include "class/display/model/modelBuffer/AllModelBuffers.h"
class ChessMaster : public Game{
public:
	ChessMaster();
	virtual ~ChessMaster();
protected:
	virtual Window* create_window();
	virtual void initialize_game();
	virtual void terminate_game();
	virtual void game_update();

	AllDrawObjects *drawObjects;
	AllTextures* textures;
	AllModelBuffers* modelBuffers;
};

#endif /* SOURCE_CLASS_GAME_CHESSMASTER_CHESSMASTER_H_ */
