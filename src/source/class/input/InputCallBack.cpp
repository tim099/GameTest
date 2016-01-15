#include "class/input/InputCallBack.h"

KeyBoard* InputCallBack::keyboard=0;
Mouse* InputCallBack::mouse=0;
InputCallBack::InputCallBack() {

}
InputCallBack::~InputCallBack() {

}
void InputCallBack::keyboard_callback(GLFWwindow *window,int key,int scancode,int action,int mods){
	keyboard->inputkey(window,key,scancode,action,mods);
}
void InputCallBack::cursor_pos_callback(GLFWwindow* window, double x, double y){
	mouse->cursor_pos_callback(window,x,y);
}
void InputCallBack::scroll_callback(GLFWwindow* window, double xoffset, double yoffset){
	mouse->scroll_callback(window,xoffset,yoffset);
}
void InputCallBack::mouse_button_callback(GLFWwindow* window, int button, int action, int mods){
	mouse->mouse_button_callback(window,button,action,mods);
}
void InputCallBack::callback_rigister(GLFWwindow *window,KeyBoard *_keyboard,Mouse *_mouse){
	keyboard=_keyboard;
	mouse=_mouse;
	//window=_window;
	glfwSetKeyCallback(window,keyboard_callback);
	glfwSetCursorPosCallback(window,cursor_pos_callback);
	glfwSetScrollCallback(window,scroll_callback);
	glfwSetMouseButtonCallback(window,mouse_button_callback);
}
