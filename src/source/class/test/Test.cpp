#include "class/test/Test.h"
#include "class/display/texture/texture3D/Texture2DArr/Texture2DArr.h"
#include "class/display/texture/texture2D/Texture2D.h"
#include "class/display/draw/texture/DrawTexture.h"
#include "class/display/texture/texture2D/drawDataEX/SobelData.h"
#include "class/display/texture/texture2D/drawDataEX/ColorAlter.h"
#include "class/display/font/RenderString.h"
#include "class/test/TestTask.h"
#include "class/input/mouse/selectable/SelectableControl.h"
#include "class/display/UI/panel/Panel.h"
#include "class/display/UI/UIObjectCreator.h"
#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <windows.h>

//#include <wglew.h>
//#include <chrono>
Test::Test() {
	sun_col1 = glm::vec3(2.2, 2.3, 2.5);
	sun_col2 = glm::vec3(1.2, 0.9, 0.5);
	timeloop = 0;
	loop_time = 10000;
	shadow_dis = 1.0;
	start_time = 0.0;
	fps = 0.0;
	end = false;
	stop = false;
	display_time = false;
	shader_at = 0;

	position_pool = new Tim::ObjPool<Position>(100);
	controller_system=new ControllerSystem();
	controller_system->push(new SelectableControl());

	map = new Map();
	map->load_map("files/maps/map011");
	window = new Window(glm::ivec2(1366, 733), "Age of Cube", false); //must before any draw obj
	//window = new Window(glm::ivec2(1920, 1080), "Age of Cube", true); //must before any draw obj

	draw = new Draw();

	textures=new AllTextures("files/script/loadTexture/loadAllTexture.txt");

	dmap = new DisplayMap(map, draw, textures, window);

	lightControl = new LightControl(120);

	input = new Input(window->get_window());
	receiver = new Receiver("test");
	input->push_receiver(receiver);

	camera = new Camera(glm::vec3(36.0, 24.0, 24.0),
			glm::vec3(34.0, 22.0, 27.0), glm::vec3(0, 1, 0), 60.0, 0.1f,
			10000.0f);

	renderer = new Renderer(lightControl, draw, window, camera, input->mouse,
			textures, &shadow_dis);

	creat_light();
	prepare_draw_obj();

	UI = new UI::UI();
	UI->Load_script("files/script/UIscript/saveUI.txt");

	render_thread = new Tim::Thread(REALTIME_PRIORITY_CLASS);
	thread_pool = new Tim::ThreadPool(8);
	render_task = new RenderTask(renderer, window);

	dmap->gen_map_obj(thread_pool);
	window->render_off(); //release window for other thread
}
Test::~Test() {
	window->render_on();
	delete render_task;
	thread_pool->Terminate();
	render_thread->Terminate();
	delete UI;
	delete renderer;
	delete camera;
	delete input;
	delete lightControl;

	delete dmap;
	delete draw;

	for (unsigned i = 0; i < b_objs.size(); i++) {
		delete b_objs.at(i);
	}
	for(unsigned i=0;i<models.size();i++){
		delete models.at(i);
	}
	delete map;
	delete textures;
	delete window;
	delete controller_system;
	delete position_pool;

}
void Test::handle_signal() {
	//Signal *sig=receiver->get_signal();
	Signal *sig = input->get_signal("test"); //get signal from receiver "test"
	if (sig) {
		std::cout << "got signal:" << sig->get_data() << std::endl;
		if (sig->get_data() == "P") {
			renderer->switch_shader("NormalMapping");
		} else if (sig->get_data() == "L") {
			renderer->switch_shader("LightScatter");
		}
	}
	sig = input->get_signal();
	if (sig) {
		std::cout << "got signal default:" << sig->get_data() << std::endl;
		if (sig->get_data() == "O") {
			renderer->switch_shader("Basic");
		}else if(sig->get_data()=="QWQ"){
			pic_but2->hide^=1;
		}else if(sig->get_data()=="QAQ"){
			pic_but->hide^=1;
		}else if(sig->get_data()=="Quit"){
			end=true;
		}
	}
}
void Test::handle_input() {
	if (input->mouse->mid_pressed()) {
		//std::cout<<"move"<<(int)(mouse->pos.x)<<","<<(int)mouse->prev_pos.x<<std::endl;
		camera->rotate(glm::vec3(0, 1, 0), -0.15 * input->mouse->pos_delta().x);
		camera->rotate(camera->yaw_vec(), 0.15 * input->mouse->pos_delta().y);
	}
	if (input->keyboard->pressed('Q')) {
		Position *pos=Tim::ObjPool<Position>::mycreate();
		if(pos)pos->initialize(input->mouse->world_pos, glm::vec3());
		ico->push_drawdata(new DrawDataObj(pos));
	}
	if (input->keyboard->get('E')) {
		camlight->shadow ^= 1;
	}
	if (input->keyboard->get(256)) { //ESC
		std::cout << "END" << std::endl;
		end = true;
	}
	if (input->mouse->right_pressed()) {
		camera->v += (float) (0.001f * sqrt(camera->look_dis() + 0.001)
				* input->mouse->pos_delta().y) * camera->look_vec_xz();
		camera->v += (float) (-0.001f * sqrt(camera->look_dis() + 0.001)
				* input->mouse->pos_delta().x)
				* glm::cross(camera->look_vec_xz(), glm::vec3(0, 1, 0));
	}
	if (input->mouse->left_pressed()) {
		camera->v += (float) (-0.0005f * sqrt(camera->look_dis() + 0.001)
				* input->mouse->pos_delta().y) * glm::vec3(0, 1, 0);
		camera->v += (float) (-0.001f * sqrt(camera->look_dis() + 0.001)
				* input->mouse->pos_delta().x)
				* glm::cross(camera->look_vec_xz(), glm::vec3(0, 1, 0));
	}
	if (input->mouse->scroll) {
		camera->dis_alter_v += sqrt(camera->look_dis() + 0.1)
				* (0.05 * input->mouse->scroll);
	}
	if (input->keyboard->pressed('M')) {
		timeloop++;
		if (timeloop >= loop_time)
			timeloop = 0;
		//sunlight->pos=glm::vec3(glm::rotate(0.5f,glm::vec3(-1,0,1))*glm::vec4(sunlight->pos,1));
	}
	if (input->keyboard->pressed('J')) {
		timeloop--;
		if (timeloop < 0)
			timeloop = loop_time - 1;
		//sunlight->pos=glm::vec3(glm::rotate(-0.5f,glm::vec3(-1,0,1))*glm::vec4(sunlight->pos,1));
	}
	if (input->keyboard->get('H')) {
		loop_time *= 1.05;
		timeloop *= 1.05;
	}
	if (input->keyboard->get('Y')) {
		loop_time *= 0.95;
		timeloop *= 0.95;
		if (loop_time < 10)
			loop_time = 10;
	}
	if (input->keyboard->get('N')) {
		stop ^= 1;
	}
	if (input->keyboard->pressed('B')) {
		glm::ivec3 pos = Map::convert_position(camera->look_at);
		if (!map->get(pos.x, pos.y, pos.z)) {
			if (map->set(pos.x, pos.y, pos.z, 1)) {
				dmap->update_map(pos);
			}
		}
	}
	if (input->keyboard->pressed('V')) {
		glm::ivec3 pos = Map::convert_position(camera->look_at);
		if (map->get(pos.x, pos.y, pos.z)) {
			if (map->set(pos.x, pos.y, pos.z, 0)) {
				dmap->update_map(pos);
			}
		}
	}

	if (input->keyboard->get(GLFW_KEY_LEFT)) {
		UI::PictureButton* but;
		but = new UI::PictureButton(glm::vec2(0.35, 1.0),"UI/button2", 0.14);
		but->set_signal(new Signal("P", "test"));
		but->set_string(new std::string(input->keyboard->get_str()));
		UI->push_child(but);
	}
	if (input->keyboard->get(GLFW_KEY_RIGHT)) {

	}
	if (input->keyboard->pressed(GLFW_KEY_UP)) {
		if (shadow_dis > 0.01)
			shadow_dis *= 0.98;
	}
	if (input->keyboard->pressed(GLFW_KEY_DOWN)) {
		if (shadow_dis < 30.0)
			shadow_dis *= 1.01;
	}
	if (input->keyboard->get('C')) {
		Position *pos=position_pool->create();
		if(pos)pos->initialize(camera->look_at + glm::vec3(0, 0.1, 0),
				glm::vec3(0, camera->look_ry(), 0));
		look_at->push_drawdata(new DrawDataObj(pos));
		lightControl->push_point_light(
				new PointLight(camera->look_at, camlight->color,
						camlight->shadow));
	}
	if (input->keyboard->get('1')) {
		camlight->color += glm::vec3(0.3, 0.0, 0.0);
	}
	if (input->keyboard->get('2')) {
		camlight->color += glm::vec3(-0.3, 0.0, 0.0);
	}
	if (input->keyboard->get('3')) {
		camlight->color += glm::vec3(0.0, 0.3, 0.0);
	}
	if (input->keyboard->get('4')) {
		camlight->color += glm::vec3(0.0, -0.3, 0.0);
	}
	if (input->keyboard->get('5')) {
		camlight->color += glm::vec3(0.0, 0.0, 0.3);
	}
	if (input->keyboard->get('6')) {
		camlight->color += glm::vec3(0.0, 0.0, -0.3);
	}
	if (input->keyboard->pressed('7')) {
		camlight->color += glm::vec3(0.05, 0.05, 0.05);
	}
	if (input->keyboard->get('8')) {
		camlight->color += glm::vec3(-0.05, -0.05, -0.05);
	}
	if (input->keyboard->get('9')) {
		camlight->color = glm::vec3(0.05, 0.05, 0.05);
	}
	if (input->keyboard->get('0')) {
		camlight->color = glm::vec3(((rand() % 10000) / 4000.0),
				((rand() % 10000) / 4000.0), ((rand() % 10000) / 4000.0));
	}
	if (input->keyboard->get('I')) {
		dmap->range += 10;
	}
	if (input->keyboard->get('K')) {
		if (dmap->range > 10)
			dmap->range -= 10;
		else
			dmap->range = 0;
	}

	if (input->keyboard->pressed('T')) {
		camera->rotate(camera->yaw_vec(), 1);
	}
	if (input->keyboard->pressed('G')) {
		camera->rotate(camera->yaw_vec(), -1);
	}
	if (input->keyboard->pressed('Z')) {
		camera->move(glm::vec3(0, 0.03, 0));
	}
	if (input->keyboard->pressed('X')) {
		camera->move(glm::vec3(0, -0.03, 0));
	}
	if (input->keyboard->pressed_char('w')) {
		dmap->max_y_alter(1, thread_pool);
	}
	if (input->keyboard->pressed_char('s')) {
		dmap->max_y_alter(-1, thread_pool);
	}
	if (input->keyboard->pressed('A')) {
		camera->move_side(0.04f);
	}
	if (input->keyboard->pressed('D')) {
		camera->move_side(-0.04f);
	}
}
void Test::set_obj_pos(Camera *camera) {
	static Position starpos(glm::vec3(0, 0, 0), glm::vec3());
	static Position sunpos(glm::vec3(5.1, 80.6, 0.1), glm::vec3());
	//obj move
	starpos.set_ry(360.0f * ((float) timeloop / loop_time));
	glm::vec3 sun_pos = glm::vec3(
			glm::rotate(360.0f * ((float) timeloop / loop_time),
					glm::vec3(-1, 0, 1))
					* glm::vec4(glm::vec3(300, 0, 500), 1));
	s_light->vec = -sun_pos;

	s_light->color = (1.0f - ((float) timeloop / loop_time)) * sun_col1
			+ ((float) timeloop / loop_time) * sun_col2;

	sunpos.set_pos(sun_pos);
	sun->push_temp_drawdata(new DrawDataObj(&sunpos));
	float tiger_ry=360.0f * ((float) timeloop / loop_time);

	static Position tiger_pos;
	tiger_pos.initialize(glm::vec3(33.0, 21.47, 26.0),
			glm::vec3(0,tiger_ry, 0));
	tiger->push_temp_drawdata(new DrawDataObj(&tiger_pos));
	static Position cam_look_at;
	cam_look_at.initialize(camera->look_at, glm::vec3(0, camera->look_ry(), 0));
	look_at->push_temp_drawdata(new DrawDataObj(&cam_look_at));

	stars->push_temp_drawdata(new DrawDataObj(&starpos));

	galaxy->push_temp_drawdata(new DrawDataObj(&starpos));

}
void Test::update_map(Camera *camera) {
	dmap->draw_map(camera); //push position
	camlight->pos = camera->look_at;
	set_obj_pos(camera);
}
void Test::prepare_draw_obj() {
	Model* m = Model::load_obj("files/obj/tiger.obj", 2.0);
	Model* m2 = Model::load_obj("files/obj/cube.obj", 40.0);
	Model* m3 = Model::load_obj("files/obj/ico.obj", 0.05);
	Model* m4 = Model::load_obj("files/obj/stars.obj", 10000.0);
	Model* m5 = Model::load_obj("files/obj/celestialSphere.obj", 16000.0);
	Model* m6 = Model::load_obj("files/obj/cube.obj", 40000.0);
	Model* m7 = Model::load_obj("files/obj/base.obj", 3.0);
	Model* m8 = Model::load_obj("files/obj/celestialSphere.obj", 15.0);
	Model* m9 = Model::load_obj("files/obj/celestialSphere.obj", 6.0);
	m->mat = glm::vec4(0.1, 1.0, 0.02, 0.05);
	m2->mat = glm::vec4(0.1, 0.1, 0.02, 1.0); //x=diffuse,y=specular_value,z=ambient,w=emissive
	//m3->mat=glm::vec4(0.1,0.05,0.02,0.05);
	m4->mat = glm::vec4(0.4, 0.05, 0.02, 1.7);
	m5->mat = glm::vec4(0.0, 0.0, 0.02, 0.1);
	m6->mat = glm::vec4(0.0, 0.0, 0.02, 0.8);
	m8->mat = glm::vec4(0.1, 0.1, 0.02, 0.5);
	m9->mat = glm::vec4(0.1, 0.1, 0.02, 0.5);
	models.push_back(m);
	models.push_back(m2);
	models.push_back(m3);
	models.push_back(m4);
	models.push_back(m5);
	models.push_back(m6);
	models.push_back(m7);
	models.push_back(m8);
	models.push_back(m9);
	b_objs.push_back(new BufferObject(m, false));
	b_objs.push_back(new BufferObject(m2, false));
	b_objs.push_back(new BufferObject(m3, false));
	b_objs.push_back(new BufferObject(m4, false));
	b_objs.push_back(new BufferObject(m5, false));
	b_objs.push_back(new BufferObject(m6, false));
	b_objs.push_back(new BufferObject(m7, false));
	b_objs.push_back(new BufferObject(m8, false));
	b_objs.push_back(new BufferObject(m9, false));

	tiger = new DrawObject(b_objs.at(0), textures->get_tex("test/test"));

	draw->push(tiger);
	sun = new DrawObject(b_objs.at(1), textures->get_tex("test/test2"));
	sun->draw_shadow = false;
	draw->push(sun);
	look_at = new DrawObject(b_objs.at(2),
			textures->get_tex("test/test3"));
	look_at->draw_shadow = false;
	draw->push(look_at);
	stars = new DrawObject(b_objs.at(3), textures->get_tex("test/test3"),
			textures->get_tex("test/NormalTexture"));
	stars->draw_shadow = false;
	draw->push(stars);
	galaxy = new DrawObject(b_objs.at(4),
			textures->get_tex("test/galaxy"),
			textures->get_tex("test/NormalTexture"));
	draw->push(galaxy);
	DrawObject* doge = new DrawObject(b_objs.at(5),
			textures->get_tex("test/doge"),
			textures->get_tex("test/NormalTexture"));
	doge->draw_shadow = false;
	draw->push(doge);
	Position* doge_pos=position_pool->create();
	doge_pos->initialize(glm::vec3(0, 0, 0), glm::vec3());
	doge->push_drawdata(new DrawDataObj(doge_pos));

	ico = new DrawObject(b_objs.at(2), textures->get_tex("test/test3"));
	draw->push(ico);
	moon = new DrawObject(b_objs.at(8), textures->get_tex("test/doge"));
	draw->push(moon);
}
void Test::creat_light() {
	camlight = new PointLight(glm::vec3(5.1, 2.6, 0.1),
			glm::vec3(3.2, 3.2, 3.2), true);
	lightControl->push_point_light(camlight);

	s_light = new ParallelLight(glm::vec3(-300, 0, -500), sun_col1, true);

	//lightControl->push_parallel_light(new ParallelLight(glm::vec3(1.0,-1.2,0.2),glm::vec3(0.2,0.2,0.2),true));
	lightControl->push_parallel_light(s_light);
}
void Test::draw_start() {
	render_thread->push_task(render_task);
	render_thread->start();
}
void Test::update() {
	//=======================logical operation and input part==========================
	if (!stop) {
		if (timeloop < loop_time)
			timeloop++;
		else
			timeloop = 0;
	}

	input->update(window->get_size());	//world space pos update by renderer

	//=======================render data update=======================================
	//glm::vec2 pos = Tim::Math::convert_to_texcoord(input->mouse->screen_pos);
	//DrawData* data = new DrawData2D(1.0, pos, 0.03);
	//data->ex_datas.push_back(new SobelData(glm::vec2(20, 10)));
	//data->ex_datas.push_back(new ColorAlter(glm::vec3(0.3, 0, 0)));
	//draw->push(new DrawTexture(texmap->get_tex(std::string("doge")), data));//texmap->get_tex(std::string("test"))
	//draw->push(new RenderString(input->keyboard->get_str(), 0.015,glm::vec2(0.0, 0.8)));

	char fpsbuff[20];
	sprintf(fpsbuff, "fps=%.2lf\n", fps);
	draw->push(new RenderString(fpsbuff, 0.015, glm::vec2(0.0, 1.0)));


	UI->update_UIObject();
	controller_system->update();
	handle_input();
	handle_signal();
	map->tic();
	camera->tic();
	//==================logical update render data==============
	UI->draw_UIObject(draw);
	update_map(camera);
	//==========================================================

	//std::cout<<"draw start"<<std::endl;
	//thread_pool->push_task(new TestTask());
	//thread_pool->push_task(new TestTask());
	//========================render thread start========================
	draw_start();
	//========================wait for rendering end=====================
	render_thread->join();
	swap_buffer();
	draw->clear_tmp_pos();
	//===================================================================

}
void Test::swap_buffer() {

	while ((1.0 / (glfwGetTime() - start_time)) > 60.0)
		;
	fps = 1.0 / (glfwGetTime() - start_time);

	//std::cout << "fps=" <<  << std::endl;
	start_time = glfwGetTime();
	window->render_on();
	window->swap_buffer();
	window->render_off();    //release thread using this window
}
void Test::Mainloop() {
	//wglSwapIntervalEXT(1);
	//window->render_off();
	//int i=WAIT_ABANDONED;
	//glfwSwapInterval(60);
	start_time = glfwGetTime();

	while (!window->WindowShouldClose() && !end) {
		update();
	}
	UI->Save_script("files/script/UIscript/saveUI.txt");
	//terminate();

}
