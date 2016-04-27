#include "class/input/keyboard/KeyBoard.h"
#include <iostream>
#include <cstdio>
namespace Input{
KeyBoard* KeyBoard::rigister_keyboard = 0;
KeyBoard::KeyBoard() {
	cur_char = 0;
}
KeyBoard::~KeyBoard() {

}
KeyBoard* KeyBoard::get_cur_keyBoard(){
	return rigister_keyboard;
}
void KeyBoard::callback_rigister(GLFWwindow *window) {
	rigister_keyboard = this;
	glfwSetKeyCallback(window, keyboard_callback);
	glfwSetCharModsCallback(window, character_callback);
}
void KeyBoard::keyboard_callback(GLFWwindow *window, int key, int scancode,
		int action, int mods) {

	rigister_keyboard->inputkey(window, key, scancode, action, mods);
}
void KeyBoard::character_callback(GLFWwindow* window, unsigned int codepoint,
		int mods) {

	rigister_keyboard->character_input(window, codepoint, mods);
}
void KeyBoard::character_input(GLFWwindow* window, unsigned int codepoint,
		int mods) {
	//std::cout<<"key press:"<<codepoint<<","<<(char)codepoint<<",mods:"<<mods<<std::endl;
	cur_char = codepoint;
	chars.insert(codepoint);
}
void KeyBoard::inputkey(GLFWwindow *window, int key, int scancode, int action,
		int mods) {
	switch (action) {
	case GLFW_PRESS:
		key_press(key, scancode, mods);
		break;
	case GLFW_RELEASE:
		key_release(key, scancode, mods);
		break;
	case GLFW_REPEAT:
		key_repeat(key, scancode, mods);
		break;
	default:
		std::cout << "unknow keyboard action" << action << std::endl;
	}
}
std::string KeyBoard::get_str()const{
	return input_str;
}
void KeyBoard::update() {
	if(cur_char>0&&cur_char<256)input_str+=(char)cur_char;
	cur_char=0;
	chars.clear();
}
bool KeyBoard::get(int key) {
	if (keys.find(key) == keys.end())
		return false;
	else
		keys.erase(key);
	return true;
}
bool KeyBoard::pressed(int key) {
	if (keys.find(key) == keys.end())
		return false;
	return true;
}
bool KeyBoard::get_char(unsigned key) {
	if (chars.find(key) == chars.end())
		return false;
	else
		chars.erase(key);
	return true;
}
unsigned KeyBoard::get_char(){
	unsigned c=cur_char;
	cur_char=0;
	return c;
}
bool KeyBoard::pressed_char(unsigned key) {
	if (chars.find(key) == chars.end())
		return false;
	return true;
}

void KeyBoard::key_press(int key, int scancode, int mods) {
	//std::cout<<"key press:"<<key<<","<<(char)key<<",scancode:"<<scancode<<",mods:"<<mods<<std::endl;
	if(key==257){//ENTER
		cur_char='\n';
	}else if(key==258){//TAB
		cur_char='	';
	}else if(key==259){//backspace
		if(!input_str.empty())input_str.resize(input_str.size()-1);
	}
	keys.insert(key);

}
void KeyBoard::clear_input_str(){
	input_str.clear();
}
void KeyBoard::clear_keys(){
	keys.clear();
}
void KeyBoard::clear_chars(){
	chars.clear();
}
void KeyBoard::clear(){
	clear_keys();
	clear_chars();
	clear_input_str();
	cur_char=0;
}
void KeyBoard::key_release(int key, int scancode, int mods) {
	//std::cout<<"key release:"<<(char)key<<",scancode:"<<scancode<<",mods:"<<mods<<std::endl;
	keys.erase(key);
}
void KeyBoard::key_repeat(int key, int scancode, int mods) {
	//std::cout<<"key repeat:"<<(char)key<<",scancode:"<<scancode<<",mods:"<<mods<<std::endl;
}
}
