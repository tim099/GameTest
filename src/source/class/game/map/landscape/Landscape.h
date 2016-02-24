#ifndef SOURCE_CLASS_GAME_MAP_LANDSCAPE_LANDSCAPE_H_
#define SOURCE_CLASS_GAME_MAP_LANDSCAPE_LANDSCAPE_H_

#include "class/game/map/cube/CubeEX.h"

class Landscape: public CubeEX {
	static bool landscape_inited;
public:
	static void  Landscape_init();
	/*
	 * this function is prepare for the initialization of static class member
	 * (for something like drawObject...
	 */
	virtual void landscape_pre_init();

	Landscape();
	virtual ~Landscape();
	virtual Landscape* create_landscape(){
		return 0;
	}
	virtual std::string get_name()const{
		return "Landscape";
	}
};

#endif /* SOURCE_CLASS_GAME_MAP_LANDSCAPE_LANDSCAPE_H_ */
