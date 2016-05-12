#ifndef SOURCE_CLASS_DISPLAY_DRAW_DRAWOBJECT_DRAWDATA_DRAWDATAOBJ_H_
#define SOURCE_CLASS_DISPLAY_DRAW_DRAWOBJECT_DRAWDATA_DRAWDATAOBJ_H_

#include "class/display/draw/drawData/DrawData.h"
#include "class/tim/math/Position.h"
namespace Display{
class DrawDataObj: public Display::DrawData {
public:
	/*
	 * not handle the delete of pos
	 */
	DrawDataObj();
	DrawDataObj(math::Position* pos,bool draw_shadow=true,bool delete_pos=false);
	virtual ~DrawDataObj();
	void set_pos(math::Position* pos);
	bool draw_shadow;
	bool delete_pos;
	math::Position* pos;
protected:

};
}
#endif /* SOURCE_CLASS_DISPLAY_DRAW_DRAWOBJECT_DRAWDATA_DRAWDATAOBJ_H_ */
