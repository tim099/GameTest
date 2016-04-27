#ifndef SOURCE_CLASS_DISPLAY_FONT_DRAWTEXTURESTR_H_
#define SOURCE_CLASS_DISPLAY_FONT_DRAWTEXTURESTR_H_

#include "class/display/draw/texture/DrawTexture.h"
namespace Display{
class DrawTextureStr: public DrawTexture {
public:
	DrawTextureStr(Texture *tex,DrawData* data);
	virtual ~DrawTextureStr();
};
}
#endif /* SOURCE_CLASS_DISPLAY_FONT_DRAWTEXTURESTR_H_ */
