#ifndef SOURCE_CLASS_GAME_SCENE_AGEOFCUBESCENE_SCENESTART_H_
#define SOURCE_CLASS_GAME_SCENE_AGEOFCUBESCENE_SCENESTART_H_

#include "class/game/scene/Scene.h"

class SceneStart: public Scene {
public:
	SceneStart();
	virtual ~SceneStart();
	virtual void pause();
	/*
	 * define behavior when this scene resume from pause state
	 */
	virtual void resume();
protected:
	virtual void scene_initialize();
	virtual void scene_update();


};

#endif /* SOURCE_CLASS_GAME_SCENE_AGEOFCUBESCENE_SCENESTART_H_ */
