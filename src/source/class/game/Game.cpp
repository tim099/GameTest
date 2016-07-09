#include "class/game/Game.h"
#include "class/input/mouse/selectable/SelectableControl.h"
#include "class/audio/AudioController.h"
#include "class/game/SceneInitTask.h"
#include "class/tim/string/String.h"
#include "class/display/light/shadow/ShadowData.h"
#include <string>
#include <iostream>
#include <fstream>
Game::Game() {
	init();
	folder_path="files/default/";
}
void Game::init(){
	end=false;
	restart=false;
	terminated=false;
	loading=false;
	frame_start_time=0.0;
	fps=0.0;
	max_fps=60.0;

	window=0;
	draw=0;
	UIObj_Creator=0;
	renderer = 0;
	//render_task = 0;

	input=0;
	game_receiver=0;
	controller_system=0;
	s_loading=0;
	//render_thread = 0;
	thread_pool = 0;
}
Game::~Game() {

	//std::cout<<"delete window"<<std::endl;

}
Display::Window* Game::create_window(){
	return (new Display::Window(config.window_size,window_name(),config.full_screen));
}
Tim::ThreadPool* Game::create_thread_pool(){
	return new Tim::ThreadPool(8,REALTIME_PRIORITY_CLASS);
}
void Game::initialize(){
	init();
	config.load(folder_path+"config.txt");
	window=create_window();

	//window->render_on();
	draw = new Display::Draw();
	draw->register_cur();
	UIObj_Creator=new UI::UIObjectCreator();
	UIObj_Creator->register_cur();

	renderer = new Display::Renderer(draw, window);
	//render_task = new RenderTask(renderer);


	input = new Input::Input(window->get_window());
	input->register_cur();
	game_receiver=new Input::Receiver("Game");
	input->push_receiver(game_receiver);

	controller_system=new ControllerSystem();
	controller_system->push(new Input::SelectableControl());
	controller_system->push(new Audio::AudioController());


	thread_pool = create_thread_pool();

	s_loading = new LoadingScene();
	s_loading->initialize(draw,input,thread_pool);

	initialize_game();
}
void Game::terminate(){
	//std::cout<<"terminate start"<<std::endl;
	//window->render_on();
	while(!scenes.empty()){
		pop_scene();
	}
	terminate_game();


	s_loading->terminate();
	delete s_loading;

	thread_pool->Terminate();

	delete controller_system;

	delete input;

	delete renderer;
	delete UIObj_Creator;
	delete draw;

	delete window;
	config.save(folder_path+"config.txt");
	//std::cout<<"terminate end"<<std::endl;
}
Scene* Game::get_cur_scene(){
	if(scenes.empty()){
		return 0;
	}else if(loading){
		return s_loading;
	}

	return scenes.back();
}
void Game::push_scene(Scene* scene){
	Scene* cur_scene=get_cur_scene();
	loading=true;
	if(cur_scene){
		cur_scene->pause();
	}
	scene->initialize(draw,input,thread_pool);
	thread_pool->push_task(new SceneInitTask(this,scene));
	//scene_push(scene);
}
void Game::scene_loading(Scene* scene){
	scene->loading();
	scenes.push_back(scene);
	loading=false;
}
void Game::pop_scene(){
	std::cout<<"Game::pop_scene() 1"<<std::endl;
	if(scenes.empty())return;
	scenes.back()->terminate();
	delete scenes.back();
	std::cout<<"Game::pop_scene() 2"<<std::endl;
	scenes.pop_back();
	std::cout<<"Game::pop_scene() 3"<<std::endl;
	Scene* cur_scene=get_cur_scene();
	if(cur_scene){
		cur_scene->resume();
	}
	std::cout<<"Game::pop_scene() 4"<<std::endl;
}
void Game::handle_game_signal(){
	Input::Signal *sig = game_receiver->get_signal(); //get signal from receiver "test"
	if (sig) {
		std::vector<std::string> strs;
		Tim::String::split(sig->get_data(),"_",strs);
		std::cout << "got signal:" << sig->get_data() << std::endl;
		if (sig->get_data() == "Quit") {
			end=true;
		}else if(sig->get_data()=="push_scene"){
			push_scene((Scene*)sig->ex_data);
			delete sig;
		}else if(sig->get_data()=="pop_scene"){
			pop_scene();
		}else if(strs.at(0)=="resolution"){
			std::cout <<"set_resolution:"<<strs.at(1)<<","<<strs.at(2)<< std::endl;
			config.window_size.x=Tim::String::str_to_int(strs.at(1));
			config.window_size.y=Tim::String::str_to_int(strs.at(2));
			config.full_screen=false;
			restart=true;
		}else if(sig->get_data()=="Window_Mode"){
			config.full_screen=false;
			restart=true;
		}else if(sig->get_data()=="Full_Screen"){
			config.full_screen=true;
			config.window_size=Display::Window::get_screen_resolution();
			restart=true;
		}else if(strs.at(0)=="shadow"){
			if(strs.at(1)=="quality"){
				if(strs.at(2)=="low"){
					config.shadow_quality=Display::ShadowLowQuality;
				}else if(strs.at(2)=="normal"){
					config.shadow_quality=Display::ShadowNormalQuality;
				}else if(strs.at(2)=="high"){
					config.shadow_quality=Display::ShadowHighQuality;
				}
			}else if(strs.at(1)=="enable"){
				if(strs.at(2)=="pssm"){
					config.enable_pssm=true;
				}
			}else if(strs.at(1)=="disable"){
				if(strs.at(2)=="pssm"){
					config.enable_pssm=false;
				}
			}
			restart=true;
		}
	}
}
void Game::update(){
	//std::cout<<"Game::update() 1"<<std::endl;
	input->update();
	handle_game_signal();

	//===========game update===============
	game_update();
	Scene* cur_scene=get_cur_scene();
	//std::cout<<"Game::update() cur_scene="<<cur_scene->scene_name()<<std::endl;
	//===============system pre_update=======================
	//std::cout<<"Game::update() controller_system->pre_update()"<<std::endl;
	controller_system->pre_update();
	//std::cout<<"Game::update() controller_system->pre_update() end"<<std::endl;
	//===============scene_update()======================
	//std::cout<<"Game::update() cur_scene="<<cur_scene->scene_name()<<std::endl;
	cur_scene->update();
	//std::cout<<"Game::update() cur_scene->update() end"<<std::endl;
	//===========system update=============
	controller_system->update();
	//std::cout<<"Game::update() controller_system->update() end"<<std::endl;
	//===========update end================
	cur_scene->scene_update_end();
	//===========draw start================
	//std::cout<<"Game::update() cur_scene->draw_scene(); start"<<std::endl;
	cur_scene->draw_scene();
	//std::cout<<"Game::update() cur_scene->draw_scene(); end"<<std::endl;
	//===========render start==============
	//std::cout<<"Game::update() renderer->render() start"<<std::endl;
	renderer->render();
	//std::cout<<"Game::update() renderer->render() end"<<std::endl;
	//===========wait for render end=======

	//render_thread->join();
	draw->clear_tmp_data();
	//std::cout<<"Game::update() draw->clear_tmp_data()"<<std::endl;
	swap_buffer();//swap screen buffer
	//std::cout<<"Game::update() end"<<std::endl;
}
void Game::mainloop(){
	frame_start_time = glfwGetTime();
	while (!window->WindowShouldClose()&&!end&&!restart) {
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
	//window->render_on();
	window->swap_buffer();
	//window->render_off();    //release thread using this window
}
