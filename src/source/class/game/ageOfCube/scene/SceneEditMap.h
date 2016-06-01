#ifndef SOURCE_CLASS_GAME_AGEOFCUBE_SCENE_SCENEEDITMAP_H_
#define SOURCE_CLASS_GAME_AGEOFCUBE_SCENE_SCENEEDITMAP_H_
#include "class/game/scene/Scene.h"
#include "class/game/ageOfCube/map/Map.h"
#include "class/display/camera/Camera.h"
#include "class/display/UI/UI.h"
#include "class/game/timer/Timer.h"
#include "class/display/light/LightControl.h"

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
	AOC::Map *map;
	Display::Camera *camera;
	Display::LightControl* lightControl;
	Building* constructing_building;
	math::Position galaxy_pos_o;
	math::Position galaxy_pos;
	UI::UI *UI;
	Timer timer;
	bool destruct_mode;
	bool pause_timer;
	std::string map_name;
	glm::ivec3 map_size;
};
}
#endif /* SOURCE_CLASS_GAME_AGEOFCUBE_SCENE_SCENEEDITMAP_H_ */
