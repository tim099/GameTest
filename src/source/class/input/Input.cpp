#include "class/input/Input.h"
#include <GL/glew.h>
#include <GL/glfw3.h>
#include <iostream>
namespace Input{
Input::Input(GLFWwindow *window) {
	keyboard=new KeyBoard();
	mouse=new Mouse();
	callback_rigister(window);
	default_receiver=new Receiver("default");
	push_receiver(default_receiver);
}
Input::~Input() {
	delete keyboard;
	delete mouse;
}
void Input::callback_rigister(GLFWwindow *window){
	keyboard->callback_rigister(window);
	mouse->callback_rigister(window);
}
void Input::update(){
    mouse->clear();//clear mouse delta pos before update
    keyboard->update();

    glfwPollEvents();//get all input

    mouse->update();
}
void Input::sent_signal(Signal* signal){
	Receiver* receiver=get_receiver(signal->get_sent_to());
	if(!receiver)receiver=default_receiver;
	receiver->push_signal(signal);

}
Signal* Input::get_signal(std::string name){
	Receiver* receiver=get_receiver(name);
	if(receiver){
		return receiver->get_signal();
	}
	return 0;
}
void Input::remove_receiver(std::string name){
	receiver_map.remove(name);
}
void Input::clear_receiver(){
	receiver_map = Tim::MapContainer<std::string,Receiver>();
}
Receiver* Input::get_receiver(std::string name){
	if(!receiver_map.find(name)){
		std::cerr<<"Receiver name:"<<name<<" not exist in Input."<<std::endl;
		return 0;
	}
	return receiver_map.get(name);
}
void Input::push_receiver(Receiver* receiver){
	if(receiver_map.find(receiver->get_name())){
		std::cerr<<"Receiver name:"<<receiver->get_name()<<" already exist in Input."<<std::endl;
		return;
	}
	receiver_map.push(receiver->get_name(),receiver);
}
}
