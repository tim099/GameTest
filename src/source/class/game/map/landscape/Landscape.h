#ifndef SOURCE_CLASS_GAME_MAP_LANDSCAPE_LANDSCAPE_H_
#define SOURCE_CLASS_GAME_MAP_LANDSCAPE_LANDSCAPE_H_

#include "class/game/map/cube/CubeEX.h"

class Landscape: public CubeEX {
public:
	/*
	 * this function is prepare for the initialization of static class member
	 * (for something like drawObject...
	 */
	virtual void landscape_pre_init();

	Landscape();
	virtual ~Landscape();
	virtual Landscape* get_landscape(){
		return this;
	}
	virtual Landscape* create_landscape(){
		return 0;
	}
	virtual std::string get_name()const{
		return "Landscape";
	}
protected:
	virtual void save_cubeEX(FILE * file);
	virtual void load_cubeEX(FILE * file);
	virtual void save_landscape(FILE * file);
	virtual void load_landscape(FILE * file);
};

#endif /* SOURCE_CLASS_GAME_MAP_LANDSCAPE_LANDSCAPE_H_ */
