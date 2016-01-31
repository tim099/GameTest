#ifndef SOURCE_CLASS_GAME_SCENE_AGEOFCUBESCENE_SCENESTART_H_
#define SOURCE_CLASS_GAME_SCENE_AGEOFCUBESCENE_SCENESTART_H_

#include "class/game/scene/Scene.h"
#include "class/display/UI/UI.h"
#include "class/display/UI/page/PageControl.h"
class SceneStart: public Scene {
public:
	SceneStart();
	virtual ~SceneStart();
	virtual std::string scene_name()const{
		return "SceneStart";
	}

	virtual void pause();
	/*
	 * define behavior when this scene resume from pause state
	 */
	virtual void resume();
protected:
	virtual void scene_update();
	virtual void scene_draw();

	virtual void scene_initialize();
	virtual	void scene_terminate();

	void create_new_map();
	void create_map();

	void handle_input();
	void handle_signal();
	UI::PageControl *p_control;
	UI::UI *UI;
};

#endif /* SOURCE_CLASS_GAME_SCENE_AGEOFCUBESCENE_SCENESTART_H_ */
