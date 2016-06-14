#include "class/controller/ControllerSystem.h"

ControllerSystem::ControllerSystem() {

}
ControllerSystem::~ControllerSystem() {
	for(unsigned i=0;i<controllers.size();i++){
		delete controllers.at(i);
	}
}
void ControllerSystem::pre_update(){
	for(unsigned i=0;i<controllers.size();i++){
		controllers.at(i)->pre_update();
	}
}
void ControllerSystem::update(){
	for(unsigned i=0;i<controllers.size();i++){
		controllers.at(i)->update();
	}
}
void ControllerSystem::push(Controller *controller){
	controllers.push_back(controller);
}
void ControllerSystem::remove(Controller *controller){
	for(unsigned i=0;i<controllers.size();i++){
		if(controllers.at(i)==controller){
			delete controller;
			controllers.at(i)=controllers.back();
			controllers.pop_back();
		}
	}
}
