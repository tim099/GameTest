#ifndef INPUT_H_
#define INPUT_H_
#include <glm/glm.hpp>
#include <GL/glew.h>
#include <GL/glfw3.h>

#include "class/input/mouse/Mouse.h"
#include "class/input/keyboard/KeyBoard.h"
#include "class/input/signal/Receiver.h"
#include "class/tim/globalObject/GlobalObject.h"
#include "class/tim/map/MapContainer.h"
#include <map>
class GLFWwindow;
namespace Input{
class Input : public Tim::GlobalObject<Input>{
public:
	Input(GLFWwindow *window);
	virtual ~Input();

	void callback_rigister(GLFWwindow *window);
	void update();

	Receiver* get_receiver(std::string name);
	/*
	 * get signal by receiver name
	 */
	Signal* get_signal(std::string name="default");
	/*
	 * will delete receiver inside this
	 */
	void remove_receiver(std::string name);
	void push_receiver(Receiver* receiver);
	void clear_receiver();
	void sent_signal(Signal* signal);

	KeyBoard *keyboard;
	Mouse *mouse;
	Receiver *default_receiver;
protected:
	Tim::MapContainer<std::string,Receiver> receiver_map;
	//std::map<std::string,Receiver*> receiver_map;
};
}
#endif /* INPUT_H_ */
