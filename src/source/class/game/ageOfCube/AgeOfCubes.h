#ifndef SOURCE_CLASS_GAME_AGEOFCUBES_H_
#define SOURCE_CLASS_GAME_AGEOFCUBES_H_
#include "class/game/Game.h"


#include "class/display/UI/UI.h"

#include "class/display/texture/AllTextures.h"
#include "class/display/draw/drawObject/AllDrawObjects.h"
#include "class/display/model/modelBuffer/AllModelBuffers.h"

#include "class/game/map/DisplayMap.h"

#include "class/game/map/Map.h"

//#include "class/tim/objectpool/ObjPool.h"


//#include "class/controller/ControllerSystem.h"
#include "class/game/ageOfCube/scene/SceneStart.h"

class AgeOfCubes : public Game{
public:
	AgeOfCubes();
	virtual ~AgeOfCubes();
private:
	virtual Window* create_window();
	virtual void initialize_game();
	virtual void terminate_game();
	virtual void game_update();


	AllDrawObjects *drawObjects;
	AllTextures* textures;
	AllModelBuffers* modelBuffers;
	SceneStart *startScene;

};

#endif /* SOURCE_CLASS_GAME_AGEOFCUBES_H_ */
