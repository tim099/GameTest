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

#include "class/game/ageOfCube/map/DisplayMap.h"
#include "class/tim/thread/ThreadPool.h"
#include "class/game/ageOfCube/map/Map.h"

#include "class/tim/objectpool/ObjPool.h"

#include "class/controller/ControllerSystem.h"
#include "class/display/draw/drawObject/AllDrawObjects.h"
#include "class/display/model/modelBuffer/AllModelBuffers.h"
#include "class/display/UI/UIObjectCreator.h"

#include "class/game/timer/Timer.h"
class Test {

public:
	Test();
	virtual ~Test();
	void Mainloop();

private:
	void handle_input();
	void camera_control();
	void update_obj_pos(Display::Camera *camera);
	void update_map(Display::Camera *camera);
	void prepare_draw_obj();
	void creat_light();

	void update();
	void swap_buffer();
	void draw_start();
	void handle_signal();

	glm::vec3 sun_col1,sun_col2;
	Tim::ObjPool<math::Position>*position_pool;


	Display::Draw *draw;
	Display::LightControl* lightControl;
	Display::PointLight *camlight;
	Display::ParallelLight *s_light;

	Input::Input* input;
	Input::Receiver* receiver;

	Display::AllDrawObjects *drawObjects;
	Display::AllTextures* textures;
	Display::AllModelBuffers* modelBuffers;
	Display::Window *window;
	Display::Camera *camera;

	Display::Renderer *renderer;
	//DisplayMap *dmap;
	//RenderTask *render_task;

	AOC::Map *map;
	UI::UI *UI;
	//Tim::Thread *render_thread;
	Tim::ThreadPool *thread_pool;
	ControllerSystem *controller_system;
	UI::UIObjectCreator *UIObj_Creator;
	Timer timer;
	double start_time;
	double fps;
	bool stop;
	bool display_time;
	bool end;
	bool destruct_mode;
	int timeloop,loop_time;
};

#endif /* TEST_H_ */
