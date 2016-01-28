#ifndef SOURCE_CLASS_GAME_SCENE_SCENE_H_
#define SOURCE_CLASS_GAME_SCENE_SCENE_H_
#include "class/input/Input.h"
#include "class/tim/thread/ThreadPool.h"
#include "class/controller/ControllerSystem.h"
#include "class/display/draw/Draw.h"
class Scene {
public:
	Scene();
	void initialize(Draw* draw,Input* input,Tim::ThreadPool *thread_pool);
	virtual ~Scene();
	/*
	 * define behavior when other scene switch to active scene, and pause this scene
	 */
	virtual void pause()=0;
	/*
	 * define behavior when this scene resume from pause state
	 */
	virtual void resume()=0;

	void update();
protected:
	virtual void scene_update()=0;
	virtual void scene_initialize()=0;
	Draw* draw;
	Input* input;
	Tim::ThreadPool *thread_pool;

};

#endif /* SOURCE_CLASS_GAME_SCENE_SCENE_H_ */
