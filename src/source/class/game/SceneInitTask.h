#ifndef SOURCE_CLASS_GAME_SCENEINITTASK_H_
#define SOURCE_CLASS_GAME_SCENEINITTASK_H_

#include "class/tim/thread/task/Task.h"
class Game;
class Scene;
class SceneInitTask: public Tim::Task {
public:
	SceneInitTask(Game *game,Scene* scene);
	virtual ~SceneInitTask();
protected:
	virtual void ExecuteTask();
	Game* game;
	Scene* scene;
};

#endif /* SOURCE_CLASS_GAME_SCENEINITTASK_H_ */
