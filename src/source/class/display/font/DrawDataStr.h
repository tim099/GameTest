#ifndef SOURCE_CLASS_DISPLAY_FONT_DRAWDATASTR_H_
#define SOURCE_CLASS_DISPLAY_FONT_DRAWDATASTR_H_

#include "class/display/draw/drawData/DrawData.h"
namespace Display{
class StringRenderer;
class RenderString;
class DrawDataStr: public DrawData {
public:
	DrawDataStr(StringRenderer* strRenderer,RenderString* renderStr);
	virtual ~DrawDataStr();
	StringRenderer* strRenderer;
	RenderString* renderStr;
};
}
#endif /* SOURCE_CLASS_DISPLAY_FONT_DRAWDATASTR_H_ */
