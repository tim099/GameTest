#ifndef INPUT_H_
#define INPUT_H_
#include <glm/glm.hpp>
#include "class/input/mouse/Mouse.h"
#include "class/input/keyboard/KeyBoard.h"
#include "class/input/InputCallBack.h"
class GLFWwindow;
class Input {
public:
	Input(GLFWwindow *window);
	virtual ~Input();
	void callback_rigister(GLFWwindow *window);
	void update(glm::vec2 window_size);

	KeyBoard *keyboard;
	Mouse *mouse;
};

#endif /* INPUT_H_ */
