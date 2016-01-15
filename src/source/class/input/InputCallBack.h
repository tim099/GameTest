#ifndef SOURCE_CLASS_INPUT_INPUTCALLBACK_H_
#define SOURCE_CLASS_INPUT_INPUTCALLBACK_H_
#include <GL/glew.h>
#include <GL/glfw3.h>
#include "class/input/keyboard/KeyBoard.h"
#include "class/input/mouse/Mouse.h"
class InputCallBack {
	static KeyBoard *keyboard;
	static Mouse *mouse;
public:
	InputCallBack();
	virtual ~InputCallBack();
	static void keyboard_callback(GLFWwindow *window,int key,int scancode,int action,int mods);
	static void cursor_pos_callback(GLFWwindow* window, double x, double y);
	static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
	static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
	static void callback_rigister(GLFWwindow *_window,KeyBoard *_keyboard,Mouse *_mouse);


};

#endif /* SOURCE_CLASS_INPUT_INPUTCALLBACK_H_ */
