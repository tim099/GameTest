#ifndef SOURCE_CLASS_GAME_MAP_CONTROLLER_H_
#define SOURCE_CLASS_GAME_MAP_CONTROLLER_H_
#include "class/controller/Component.h"

class Controller {

public:
	Controller();
	virtual ~Controller();
	void push(Component* component);
	/*
	 * update the controller
	 */
	virtual void update();

};
//#include "class/controller/Controller.cpp"
#endif /* SOURCE_CLASS_GAME_MAP_CONTROLLER_H_ */
