#ifndef DRAWTEXTURE2D_H_
#define DRAWTEXTURE2D_H_
#include "class/display/draw/texture/DrawTexture.h"
#include "class/display/texture/texture2D/Texture2D.h"
class DrawTexture2D : public DrawTexture{
public:
	DrawTexture2D(Texture2D *tex);
	virtual ~DrawTexture2D();
	virtual void draw_texture(Shader *shader);
protected:
	Texture2D *tex;
};

#endif /* DRAWTEXTURE2D_H_ */
