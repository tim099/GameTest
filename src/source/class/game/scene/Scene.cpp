#include "class/game/scene/Scene.h"

Scene::Scene() {
	input=0;
	thread_pool=0;
	draw=0;

	receiver=0;
}
Scene::~Scene() {

}
void Scene::initialize(Draw* _draw,Input* _input,Tim::ThreadPool *_thread_pool){
	input=_input;
	thread_pool=_thread_pool;
	draw=_draw;
	receiver=new Receiver(scene_name());
	input->push_receiver(receiver);
	scene_initialize();
}
void Scene::terminate(){
	scene_terminate();
	input->remove_receiver(receiver->get_name());
}
void Scene::update(){
	scene_update();
}
void Scene::draw_scene(){
	scene_draw();
}
