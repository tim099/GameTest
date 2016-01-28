#ifndef SOURCE_CLASS_DISPLAY_DRAW_DRAWOBJECT_DRAWDATA_DRAWDATAOBJ_H_
#define SOURCE_CLASS_DISPLAY_DRAW_DRAWOBJECT_DRAWDATA_DRAWDATAOBJ_H_

#include "class/display/draw/drawData/DrawData.h"
#include "class/tim/math/Position.h"
class DrawDataObj: public DrawData {
public:
	/*
	 * not handle the delete of pos
	 */
	DrawDataObj();
	DrawDataObj(Position* pos,bool draw_shadow=true);
	virtual ~DrawDataObj();
	void set_pos(Position* pos);
	bool draw_shadow;
	Position* pos;
protected:

};

#endif /* SOURCE_CLASS_DISPLAY_DRAW_DRAWOBJECT_DRAWDATA_DRAWDATAOBJ_H_ */
