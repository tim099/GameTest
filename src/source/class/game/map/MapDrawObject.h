#ifndef MAPDRAWOBJECT_H_
#define MAPDRAWOBJECT_H_
#include "class/display/draw/object/DrawObject.h"
class MapDrawObject : public DrawObject{
public:
	MapDrawObject(BufferObject* obj,Texture* texture,Texture* NormalMap=0);
	virtual ~MapDrawObject();
	virtual void update();
	void update_model();
	Model *mapmodel;

protected:
	bool updated;
};

#endif /* MAPDRAWOBJECT_H_ */
