#ifndef CALLBACKFUNC_H_
#define CALLBACKFUNC_H_
#include <GL/glew.h>
#include <GL/glfw3.h>
#include "class/input/keyboard/KeyBoard.h"
#include "class/input/mouse/Mouse.h"

void keyboard_callback(GLFWwindow *window,int key,int scancode,int action,int mods);
void cursor_pos_callback(GLFWwindow* window, double x, double y);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
void callback_rigister(GLFWwindow *_window,KeyBoard *_keyboard,Mouse *_mouse);

#endif /* CALLBACKFUNC_H_ */
