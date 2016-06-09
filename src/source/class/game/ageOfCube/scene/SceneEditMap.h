#ifndef SOURCE_CLASS_GAME_AGEOFCUBE_SCENE_SCENEEDITMAP_H_
#define SOURCE_CLASS_GAME_AGEOFCUBE_SCENE_SCENEEDITMAP_H_
#include "class/game/scene/Scene.h"
#include "class/game/ageOfCube/field/Field.h"
#include "class/display/camera/Camera.h"
#include "class/display/UI/UI.h"
#include "class/game/timer/Timer.h"
#include "class/display/light/LightControl.h"
#include "class/audio/AudioPlayer.h"
namespace AOC{
class SceneEditMap : public Scene{
public:
	SceneEditMap(std::string map_name,glm::ivec3 map_size);
	virtual ~SceneEditMap();
	virtual std::string scene_name()const{
		return "SceneEditMap";
	}
	virtual void loading();
	virtual void pause();
	virtual void resume();
	virtual void scene_update_end();
protected:
	virtual void scene_update();
	virtual void scene_draw();

	virtual void scene_initialize();
	virtual	void scene_terminate();

	virtual void handle_signal(Input::Signal *sig);

	void camera_control();
	void handle_input();
	int cube_type;
	//Map *map;
	Field* field;
	Display::Camera *camera;
	Display::LightControl* lightControl;
	Audio::AudioPlayer *back_music;
	Building* constructing_building;
	math::Position galaxy_pos_o;
	math::Position galaxy_pos;
	Display::ParallelLight *sun_light;
	glm::vec3 sun_col_1,sun_col_2,sun_pos;
	UI::UI *UI;
	Timer timer;
	bool destruct_mode;
	bool pause_timer;
	std::string map_name;
	glm::ivec3 map_size;
};
}
#endif /* SOURCE_CLASS_GAME_AGEOFCUBE_SCENE_SCENEEDITMAP_H_ */
