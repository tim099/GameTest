#ifndef SOURCE_CLASS_GAME_MAP_CONTROLLER_H_
#define SOURCE_CLASS_GAME_MAP_CONTROLLER_H_

class Controller {

public:
	Controller();
	virtual ~Controller();



	/*
	 * pre update the controller before scene update
	 */
	virtual void pre_update(){}

	/*
	 * update the controller
	 */
	virtual void update(){}

};
//#include "class/controller/Controller.cpp"
#endif /* SOURCE_CLASS_GAME_MAP_CONTROLLER_H_ */
