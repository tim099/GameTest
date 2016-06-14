#ifndef SOURCE_CLASS_GAME_CONTROLLER_CONTROLLERSYSTEM_H_
#define SOURCE_CLASS_GAME_CONTROLLER_CONTROLLERSYSTEM_H_
#include <vector>
#include "class/controller/Controller.h"

class ControllerSystem {
public:
	ControllerSystem();
	virtual ~ControllerSystem();

	/*
	 * pre update all controller in this system before scene update
	 */
	void pre_update();

	/*
	 * update all controller in this system
	 */
	void update();
	void push(Controller *controller);
	void remove(Controller *controller);
protected:
	std::vector<Controller*>controllers;
};

#endif /* SOURCE_CLASS_GAME_CONTROLLER_CONTROLLERSYSTEM_H_ */
