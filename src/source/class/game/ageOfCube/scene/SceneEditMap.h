#ifndef SOURCE_CLASS_GAME_AGEOFCUBE_SCENE_SCENEEDITMAP_H_
#define SOURCE_CLASS_GAME_AGEOFCUBE_SCENE_SCENEEDITMAP_H_
#include "class/game/scene/Scene.h"
#include "class/game/map/Map.h"
#include "class/display/camera/Camera.h"
#include "class/display/UI/UI.h"
#include "class/game/timer/Timer.h"
namespace AOC{
class SceneEditMap : public Scene{
public:
	SceneEditMap(std::string map_name,glm::ivec3 map_size);
	virtual ~SceneEditMap();
	virtual std::string scene_name()const{
		return "SceneEditMap";
	}

	virtual void pause();
	virtual void resume();
protected:
	virtual void scene_update();
	virtual void scene_draw();

	virtual void scene_initialize();
	virtual	void scene_terminate();

	void camera_control();
	void handle_input();
	Map *map;
	Camera *camera;
	LightControl* lightControl;
	CubeLight* cl;
	UI::UI *UI;
	Timer timer;
	bool destruct_mode;
	std::string map_name;
	glm::ivec3 map_size;
};
}
#endif /* SOURCE_CLASS_GAME_AGEOFCUBE_SCENE_SCENEEDITMAP_H_ */
