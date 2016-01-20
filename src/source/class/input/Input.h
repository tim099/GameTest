#ifndef INPUT_H_
#define INPUT_H_
#include <glm/glm.hpp>
#include <GL/glew.h>
#include <GL/glfw3.h>

#include "class/input/mouse/Mouse.h"
#include "class/input/keyboard/KeyBoard.h"
#include "class/input/signal/Receiver.h"
#include <map>
class GLFWwindow;
class Input {

public:
	Input(GLFWwindow *window);
	virtual ~Input();

	void callback_rigister(GLFWwindow *window);
	void update(glm::vec2 window_size);

	Receiver* get_receiver(std::string name);
	/*
	 * get signal by receiver name
	 */
	Signal* get_signal(std::string name="default");

	void push_receiver(Receiver* receiver);
	void sent_signal(Signal* signal);

	KeyBoard *keyboard;
	Mouse *mouse;
	Receiver *default_receiver;
protected:
	std::map<std::string,Receiver*> receiver_map;
};

#endif /* INPUT_H_ */
