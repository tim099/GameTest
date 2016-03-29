#ifndef SOURCE_CLASS_GAME_MAP_WATERDRAWOBJECT_H_
#define SOURCE_CLASS_GAME_MAP_WATERDRAWOBJECT_H_

#include "class/display/draw/drawObject/DrawObject.h"

class WaterDrawObject: public DrawObject {
public:
	virtual std::string get_type()const{
		return "WaterDrawObject";
	}
	void init();
	WaterDrawObject();
	virtual ~WaterDrawObject();
	virtual void update();
	void update_model(){
		model_updated=true;
	}
	//if model_buffer not exist,create the model buffer,else update the model_buffer
	void update_model_buffer();
	Model *model;
	bool water_updated;
	bool draw;
protected:
	void clear_model_buffer();
	bool model_updated;
};

#endif /* SOURCE_CLASS_GAME_MAP_WATERDRAWOBJECT_H_ */
