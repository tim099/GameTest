#ifndef SOURCE_CLASS_GAME_MAP_WATERDRAWOBJECT_H_
#define SOURCE_CLASS_GAME_MAP_WATERDRAWOBJECT_H_

#include "class/display/draw/drawObject/DynamicDrawObject.h"

class WaterDrawObject: public Display::DynamicDrawObject {
public:
	virtual std::string get_type()const{
		return "WaterDrawObject";
	}
	void init();
	WaterDrawObject();
	virtual ~WaterDrawObject();
protected:

};

#endif /* SOURCE_CLASS_GAME_MAP_WATERDRAWOBJECT_H_ */
