#ifndef TEST_H_
#define TEST_H_

#include <GL/glew.h>
#include <GL/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>

#include "headers/callback/callBackFunc.h"
#include "class/display/shader/Shader.h"
#include "class/display/shader/shader2D/Shader2D.h"
#include "class/display/window/Window.h"

#include "class/display/texture/TextureMap.h"
#include "class/display/camera/Camera.h"

#include "class/display/model/cube/CubeModel.h"
#include "class/display/buffer/frameBuffer/FrameBuffer.h"
#include "class/input/Input.h"
#include "class/display/draw/Draw.h"

#include "class/display/render/Renderer.h"
#include "class/display/render/RenderTask.h"
#include "class/display/draw/DrawObjectCreater.h"
#include "class/display/light/LightControl.h"
#include "class/display/uniform/Uniform.h"
#include "class/game/map/DisplayMap.h"
#include "class/tim/thread/Thread.h"
#include "class/tim/thread/ThreadPool.h"
#include "class/game/map/Map.h"

class Test {

public:
	Test();
	virtual ~Test();
	void terminate();

	void input();

	void set_obj_pos(Camera *camera);
	void update_map(Camera *camera);
	void prepare_draw_obj();
	void creat_light();
	void Mainloop();
	void timer_tic(double &time);
	void test();
private:
	void swap_buffer();
	void draw(double &time);
	glm::vec3 sun_col1,sun_col2;
	std::vector<Model*>models;
	std::vector<BufferObject*>b_objs;


	double start_time;
	Draw *d_obj;
	LightControl* lightControl;
	PointLight *camlight;
	ParallelLight *s_light;
	KeyBoard *keyboard;
	Mouse *mouse;

	DrawObject* look_at;
	DrawObject* base;
	DrawObject* sun;
	DrawObject* tiger;
	DrawObject* stars;
	DrawObject* galaxy;
	DrawObject* ico;
	DrawObject* moon;


	TextureMap* texmap;


	GLuint VertexArrayID;
	Window *window;
	Camera *camera;

	Renderer *renderer;
	DisplayMap *dmap;
	RenderTask *render_task;
	Map *map;
	Tim::Thread *render_thread;
	Tim::ThreadPool *thread_pool;
	double tiger_ry;
	double shadow_dis;

	bool stop_the_sun;
	bool to_sobel;
	bool display_time;
	bool end;
	int shader_at;
	int max_point_light;
	int timeloop,loop_time;
};

#endif /* TEST_H_ */
