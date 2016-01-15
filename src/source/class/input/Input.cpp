#include "class/input/Input.h"
#include <GL/glew.h>
#include <GL/glfw3.h>
Input::Input(GLFWwindow *window) {
	keyboard=new KeyBoard();
	mouse=new Mouse();
	callback_rigister(window);
}
Input::~Input() {
	delete keyboard;
	delete mouse;
}
void Input::callback_rigister(GLFWwindow *window){
	InputCallBack::callback_rigister(window,keyboard,mouse);
}
void Input::update(glm::vec2 window_size){
    mouse->tic();//clear mouse delta pos before update
    keyboard->tic();

    glfwPollEvents();//get all input

    mouse->get_screen_space_pos(window_size);

}
