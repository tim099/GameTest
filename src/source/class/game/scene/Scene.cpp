#include "class/game/scene/Scene.h"

Scene::Scene() {
	input=0;
	thread_pool=0;
	draw=0;
}
Scene::~Scene() {

}
void Scene::initialize(Draw* _draw,Input* _input,Tim::ThreadPool *_thread_pool){
	input=_input;
	thread_pool=_thread_pool;
	draw=_draw;
	scene_initialize();
}
void Scene::update(){
	scene_update();
}
