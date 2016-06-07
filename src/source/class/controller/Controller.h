#ifndef SOURCE_CLASS_GAME_MAP_CONTROLLER_H_
#define SOURCE_CLASS_GAME_MAP_CONTROLLER_H_

class Controller {

public:
	Controller();
	virtual ~Controller();
	/*
	 * update the controller
	 */
	virtual void update();

};
//#include "class/controller/Controller.cpp"
#endif /* SOURCE_CLASS_GAME_MAP_CONTROLLER_H_ */
