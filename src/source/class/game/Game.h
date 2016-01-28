#ifndef SOURCE_CLASS_GAME_GAME_H_
#define SOURCE_CLASS_GAME_GAME_H_
#include "class/game/scene/Scene.h"

#include "class/display/window/Window.h"
#include "class/display/draw/Draw.h"
#include "class/display/render/Renderer.h"
#include "class/display/render/RenderTask.h"


#include "class/input/Input.h"
#include "class/controller/ControllerSystem.h"

#include "class/tim/thread/ThreadPool.h"
#include <vector>
class Game {
public:
	Game();
	virtual ~Game();
	virtual void mainloop();
	void initialize();
	void terminate();
protected:
	virtual void update();
	virtual void initialize_game()=0;
	virtual void terminate_game()=0;
	virtual void game_update()=0;
	virtual Window* create_window()=0;
	Scene* get_cur_scene();
	void swap_buffer();
	void push_scene(Scene* scene);
	void pop_scene();
	std::vector<Scene*>scenes;
	Window* window;
	Draw *draw;
	RenderTask *render_task;
	Renderer *renderer;

	Tim::Thread *render_thread;
	Tim::ThreadPool *thread_pool;

	Input* input;
	ControllerSystem *controller_system;
	bool end,terminated;
	double fps,max_fps;
	double frame_start_time;
};

#endif /* SOURCE_CLASS_GAME_GAME_H_ */
