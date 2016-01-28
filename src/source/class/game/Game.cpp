#include "class/game/Game.h"
#include "class/input/mouse/selectable/SelectableControl.h"
#include <iostream>
Game::Game() {
	end=false;
	terminated=false;
	frame_start_time=0.0;
	fps=0.0;
	max_fps=60.0;

	window=0;
	draw=0;
	renderer = 0;
	render_task = 0;

	input=0;
	controller_system=0;

	render_thread = 0;
	thread_pool = 0;
}
Game::~Game() {

	//std::cout<<"delete window"<<std::endl;

}
void Game::initialize(){
	window=create_window();
	draw = new Draw();
	draw->register_cur();
	renderer = new Renderer(draw, window);
	render_task = new RenderTask(renderer);

	input = new Input(window->get_window());
	input->register_cur();
	controller_system=new ControllerSystem();
	controller_system->push(new SelectableControl());

	render_thread = new Tim::Thread(REALTIME_PRIORITY_CLASS);
	thread_pool = new Tim::ThreadPool(8);
	initialize_game();

	window->render_off();
}
void Game::terminate(){
	std::cout<<"terminate start"<<std::endl;
	window->render_on();
	for(unsigned i=0;i<scenes.size();i++){
		delete scenes.at(i);
	}
	terminate_game();

	thread_pool->Terminate();
	render_thread->Terminate();

	delete controller_system;
	delete input;

	delete render_task;
	delete renderer;
	delete draw;
	delete window;
	std::cout<<"terminate end"<<std::endl;
}
Scene* Game::get_cur_scene(){
	if(scenes.empty()){
		return 0;
	}
	return scenes.back();
}
void Game::push_scene(Scene* scene){
	Scene* cur_scene=get_cur_scene();
	if(cur_scene)cur_scene->pause();
	scene->initialize(draw,input,thread_pool);
	scenes.push_back(scene);
}
void Game::pop_scene(){
	if(scenes.empty())return;

	delete scenes.back();
	scenes.pop_back();
	Scene* cur_scene=get_cur_scene();
	cur_scene->resume();
}
void Game::update(){
	input->update();
	controller_system->update();

	//===========game update=============
	game_update();
	get_cur_scene()->update();
	//===========render start=============
	render_thread->push_task(render_task);
	render_thread->start();
	//===========wait for render end=============

	render_thread->join();
	draw->clear_tmp_data();
	swap_buffer();
}
void Game::mainloop(){
	frame_start_time = glfwGetTime();
	while (!window->WindowShouldClose()&&!end) {
		update();
	}
	terminate();
}
void Game::swap_buffer(){
	while ((1.0 / (glfwGetTime() - frame_start_time)) > max_fps)
		;
	fps = 1.0 / (glfwGetTime() - frame_start_time);

	//std::cout << "fps=" <<  << std::endl;
	frame_start_time = glfwGetTime();
	window->render_on();
	window->swap_buffer();
	window->render_off();    //release thread using this window
}
