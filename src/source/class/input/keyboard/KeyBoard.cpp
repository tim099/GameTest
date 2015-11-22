#include "class/input/keyboard/KeyBoard.h"
#include <iostream>
#include <cstdio>
KeyBoard::KeyBoard() {

}
KeyBoard::~KeyBoard() {

}
void KeyBoard::inputkey(GLFWwindow *window,int key, int scancode,int action,int mods){
	switch(action){
		case GLFW_PRESS:
			key_press(key,scancode,mods);
			break;
		case GLFW_RELEASE:
			key_release(key,scancode,mods);
			break;
		case GLFW_REPEAT:
			key_repeat(key,scancode,mods);
			break;
		default:
			std::cout<<"unknow keyboard action"<<action<<std::endl;
	}
}
void KeyBoard::tic(){

}
bool KeyBoard::get(int key){
	if(keys.find(key)==keys.end())return false;
	else keys.erase(key);
	return true;
}
bool KeyBoard::pressed(int key){
	if(keys.find(key)==keys.end())return false;
	return true;
}
void KeyBoard::key_press(int key,int scancode,int mods){
	//std::cout<<"key press:"<<(char)key<<",scancode:"<<scancode<<",mods:"<<mods<<std::endl;
	//std::cout<<"key press:"<<key<<",scancode:"<<scancode<<",mods:"<<mods<<std::endl;
	keys.insert(key);
}
void KeyBoard::key_release(int key,int scancode,int mods){
	//std::cout<<"key release:"<<(char)key<<",scancode:"<<scancode<<",mods:"<<mods<<std::endl;
	keys.erase(key);
}
void KeyBoard::key_repeat(int key,int scancode,int mods){
	//std::cout<<"key repeat:"<<(char)key<<",scancode:"<<scancode<<",mods:"<<mods<<std::endl;
}
