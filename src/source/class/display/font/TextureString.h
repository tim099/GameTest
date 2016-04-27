#ifndef SOURCE_CLASS_DISPLAY_FONT_TEXTURESTRING_H_
#define SOURCE_CLASS_DISPLAY_FONT_TEXTURESTRING_H_

#include "class/display/texture/Texture.h"
namespace Display{
class TextureString: public Texture {
public:
	TextureString();
	virtual ~TextureString();
protected:
	virtual void draw(Shader2D* shader2D,DrawData *data);
};
}
#endif /* SOURCE_CLASS_DISPLAY_FONT_TEXTURESTRING_H_ */
