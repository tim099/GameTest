#ifndef TEST_H_
#define TEST_H_

#include <GL/glew.h>
#include <GL/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>

#include "class/display/shader/Shader.h"
#include "class/display/shader/shader2D/Shader2D.h"
#include "class/display/window/Window.h"
#include "class/display/UI/UI.h"
#include "class/display/texture/TextureMap.h"
#include "class/display/camera/Camera.h"

#include "class/display/model/cube/CubeModel.h"
#include "class/display/buffer/frameBuffer/FrameBuffer.h"

#include "class/display/draw/Draw.h"

#include "class/display/render/Renderer.h"
#include "class/display/render/RenderTask.h"
#include "class/display/light/LightControl.h"
#include "class/display/uniform/Uniform.h"

#include "class/input/Input.h"

#include "class/game/map/DisplayMap.h"
#include "class/tim/thread/ThreadPool.h"
#include "class/game/map/Map.h"

#include "class/tim/objectpool/ObjPool.h"
class Test {

public:
	Test();
	virtual ~Test();
	void terminate();
	void Mainloop();

private:
	void handle_input();
	void set_obj_pos(Camera *camera);
	void update_map(Camera *camera);
	void prepare_draw_obj();
	void creat_light();

	void timer_tic(double &time);
	void swap_buffer();
	void draw_start();
	void handle_signal();
	glm::vec3 sun_col1,sun_col2;
	std::vector<Model*>models;
	std::vector<BufferObject*>b_objs;
	Tim::ObjPool<Position>*position_pool;

	double start_time;
	Draw *draw;
	LightControl* lightControl;
	PointLight *camlight;
	ParallelLight *s_light;
	Input* input;
	Receiver* receiver;
	DrawObject* look_at;
	DrawObject* base;
	DrawObject* sun;
	DrawObject* tiger;
	DrawObject* stars;
	DrawObject* galaxy;
	DrawObject* ico;
	DrawObject* moon;

	TextureMap* texmap;
	TextureMap* button_texmap;
	Window *window;
	Camera *camera;

	Renderer *renderer;
	DisplayMap *dmap;
	RenderTask *render_task;
	Map *map;
	UI::UI *UI;
	UI::ButtonControl* button_control;
	Tim::Thread *render_thread;
	Tim::ThreadPool *thread_pool;
	double fps;
	double shadow_dis;
	bool stop;
	bool display_time;
	bool end;
	int shader_at;
	int timeloop,loop_time;
};

#endif /* TEST_H_ */
