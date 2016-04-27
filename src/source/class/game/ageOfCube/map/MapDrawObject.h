#ifndef MAPDRAWOBJECT_H_
#define MAPDRAWOBJECT_H_
#include "class/display/draw/drawObject/DynamicDrawObject.h"
class MapDrawObject : public Display::DynamicDrawObject{
public:
	MapDrawObject(std::string tex_str = "",
			std::string NormalTex_str = "");
	virtual ~MapDrawObject();
	virtual void init(std::string tex_str = "",
			std::string NormalTex_str = "");
protected:

};

#endif /* MAPDRAWOBJECT_H_ */
