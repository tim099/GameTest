#include "class/game/SceneInitTask.h"
#include "class/game/Game.h"
SceneInitTask::SceneInitTask(Game *_game,Scene* _scene) {
	game=_game;
	scene=_scene;
	auto_terminate=true;
}

SceneInitTask::~SceneInitTask() {

}
void SceneInitTask::ExecuteTask(){
	game->scene_loading(scene);
}
