#include "class/game/scene/Scene.h"

Scene::Scene() {
	input=0;
	thread_pool=0;
	draw=0;

	receiver=0;
}
Scene::~Scene() {

}
void Scene::initialize(Display::Draw* _draw,Input::Input* _input,Tim::ThreadPool *_thread_pool){
	input=_input;
	thread_pool=_thread_pool;
	draw=_draw;
	receiver=new Input::Receiver(scene_name());
	input->push_receiver(receiver);
	scene_initialize();
}
void Scene::terminate(){
	scene_terminate();
	input->remove_receiver(receiver->get_name());
}
void Scene::handle_signal(Input::Signal *sig){
	std::cout<<"not implement handle signal in class Scene!!"<<std::endl;
}
void Scene::get_signal(){
	Input::Signal* sig;
	while((sig=receiver->get_signal())){
		handle_signal(sig);
	}
}
void Scene::update(){
	get_signal();
	scene_update();
}
void Scene::draw_scene(){
	scene_draw();
}
