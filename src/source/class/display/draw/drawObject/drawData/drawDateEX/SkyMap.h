#ifndef SOURCE_CLASS_DISPLAY_DRAW_DRAWOBJECT_DRAWDATA_DRAWDATEEX_SKYMAP_H_
#define SOURCE_CLASS_DISPLAY_DRAW_DRAWOBJECT_DRAWDATA_DRAWDATEEX_SKYMAP_H_
#include "class/display/draw/drawData/DrawDataEX/DrawDataEX.h"
namespace Display {
namespace drawDataEX {

class SkyMap : public DrawDataEX{
public:
	SkyMap();
	virtual ~SkyMap();
	virtual void prepare_to_draw(Shader* shader2D);
	virtual void draw_end(Shader* shader2D);
};

} /* namespace drawDataEX */
} /* namespace Display */

#endif /* SOURCE_CLASS_DISPLAY_DRAW_DRAWOBJECT_DRAWDATA_DRAWDATEEX_SKYMAP_H_ */
