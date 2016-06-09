#ifndef SOURCE_CLASS_GAME_AGEOFCUBE_SCENE_SCENEPLAYTD_H_
#define SOURCE_CLASS_GAME_AGEOFCUBE_SCENE_SCENEPLAYTD_H_

#include "class/game/scene/Scene.h"
#include "class/game/ageOfCube/map/Map.h"
#include "class/display/camera/Camera.h"
#include "class/display/UI/UI.h"
#include "class/game/timer/Timer.h"
#include "class/display/light/LightControl.h"
#include "class/game/ageOfCube/map/unit/UnitController.h"
#include "class/game/ageOfCube/player/Player.h"

namespace AOC {

enum playMode{
	normal, constructing, removing
};
class Building;
class ScenePlayTD : public Scene{
public:
	ScenePlayTD(std::string _map_name, glm::ivec3 _map_size);
	virtual ~ScenePlayTD();
	virtual std::string scene_name()const{
		return "ScenePlayTD";
	}
	virtual void loading();
	virtual void pause();
	virtual void resume();
	virtual void scene_update_end();
	void reload_map();
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
	Display::CubeLight* cl;

	UI::UI *UI;
	Timer timer;
	std::string map_name;
	Building* constructing_building;
	playMode mode;
	glm::ivec3 map_size;
	Player *player;
};

} /* namespace AOC */

#endif /* SOURCE_CLASS_GAME_AGEOFCUBE_SCENE_SCENEPLAYTD_H_ */
