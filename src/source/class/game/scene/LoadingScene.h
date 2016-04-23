#ifndef SOURCE_CLASS_GAME_SCENE_LOADINGSCENE_H_
#define SOURCE_CLASS_GAME_SCENE_LOADINGSCENE_H_

#include "class/game/scene/Scene.h"

class LoadingScene: public Scene {
public:
	LoadingScene();
	virtual ~LoadingScene();
	virtual std::string scene_name()const{
		return std::string("LoadingScene");
	}
protected:
	virtual void scene_update();
	virtual void scene_draw();
	virtual void scene_initialize();
	virtual	void scene_terminate();

};

#endif /* SOURCE_CLASS_GAME_SCENE_LOADINGSCENE_H_ */
