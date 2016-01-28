#ifndef MAPDRAWOBJECT_H_
#define MAPDRAWOBJECT_H_
#include "class/display/draw/drawObject/DrawObject.h"
class MapDrawObject : public DrawObject{
public:
	MapDrawObject(std::string tex_str = "",
			std::string NormalTex_str = "");
	virtual ~MapDrawObject();
	virtual void update();
	void update_model();
	Model *mapmodel;

protected:
	bool updated;
};

#endif /* MAPDRAWOBJECT_H_ */
