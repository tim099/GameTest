#include "class/input/Input.h"
#include <GL/glew.h>
#include <GL/glfw3.h>
#include <iostream>

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
	std::map<std::string,Receiver*>::iterator it=receiver_map.begin();
	while(it!=receiver_map.end()){
		delete (it->second);
		it++;
	}
}
Input * Input::get_cur_input(){
	return get_cur_object();
}
void Input::callback_rigister(GLFWwindow *window){
	keyboard->callback_rigister(window);
	mouse->callback_rigister(window);
}
void Input::update(){
    mouse->clear();//clear mouse delta pos before update
    keyboard->clear();

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
Receiver* Input::get_receiver(std::string name){
	if(receiver_map.find(name)==receiver_map.end()){
		std::cerr<<"Receiver name:"<<name<<" not exist in Input."<<std::endl;
		return 0;
	}
	return receiver_map[name];
}
void Input::push_receiver(Receiver* receiver){
	if(receiver_map.find(receiver->get_name())!=receiver_map.end()){
		std::cerr<<"Receiver name:"<<receiver->get_name()<<" already exist in Input."<<std::endl;
		return;
	}
	receiver_map[receiver->get_name()]=receiver;
}
