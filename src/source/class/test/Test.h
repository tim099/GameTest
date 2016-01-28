#ifndef TEST_H_
#define TEST_H_


#include <vector>

#include "class/display/window/Window.h"
#include "class/display/UI/UI.h"
#include "class/display/texture/AllTextures.h"
#include "class/display/camera/Camera.h"

#include "class/display/draw/Draw.h"

#include "class/display/render/Renderer.h"
#include "class/display/render/RenderTask.h"
#include "class/display/light/LightControl.h"

#include "class/input/Input.h"

#include "class/game/map/DisplayMap.h"
#include "class/tim/thread/ThreadPool.h"
#include "class/game/map/Map.h"

#include "class/tim/objectpool/ObjPool.h"

#include "class/controller/ControllerSystem.h"
#include "class/display/draw/drawObject/AllDrawObjects.h"
#include "class/display/model/modelBuffer/AllModelBuffers.h"
class Test {

public:
	Test();
	virtual ~Test();
	void Mainloop();

private:
	void handle_input();
	void update_obj_pos(Camera *camera);
	void update_map(Camera *camera);
	void prepare_draw_obj();
	void creat_light();

	void update();
	void swap_buffer();
	void draw_start();
	void handle_signal();

	glm::vec3 sun_col1,sun_col2;
	Tim::ObjPool<Position>*position_pool;


	Draw *draw;
	LightControl* lightControl;
	PointLight *camlight;
	ParallelLight *s_light;

	Input* input;
	Receiver* receiver;

	AllDrawObjects *drawObjects;
	AllTextures* textures;
	AllModelBuffers* modelBuffers;
	Window *window;
	Camera *camera;

	Renderer *renderer;
	DisplayMap *dmap;
	RenderTask *render_task;
	Map *map;
	UI::UI *UI;
	Tim::Thread *render_thread;
	Tim::ThreadPool *thread_pool;
	ControllerSystem *controller_system;

	double start_time;
	double fps;
	bool stop;
	bool display_time;
	bool end;
	int timeloop,loop_time;
};

#endif /* TEST_H_ */
