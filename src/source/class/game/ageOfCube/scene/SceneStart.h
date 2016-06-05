#ifndef SOURCE_CLASS_GAME_SCENE_AGEOFCUBESCENE_SCENESTART_H_
#define SOURCE_CLASS_GAME_SCENE_AGEOFCUBESCENE_SCENESTART_H_

#include <string>
#include "class/game/scene/Scene.h"
#include "class/display/UI/UI.h"
#include "class/display/UI/page/PageControl.h"
#include "class/display/UI/page/AutoPageControl.h"
#include "class/audio/AudioPlayer.h"
namespace AOC{
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
	void load_map(std::string mode);
	void delete_map();

	void handle_input();
	virtual void handle_signal(Input::Signal *sig);
	std::string map_folder_path;
	UI::PageControl *p_control;
	UI::AutoPageControl *auto_p_control;
	UI::UI *UI;
	Audio::AudioPlayer music_player;
};
}
#endif /* SOURCE_CLASS_GAME_SCENE_AGEOFCUBESCENE_SCENESTART_H_ */
