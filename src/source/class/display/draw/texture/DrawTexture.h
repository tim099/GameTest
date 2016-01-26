#ifndef DRAWTEXTURE_H_
#define DRAWTEXTURE_H_
#include "class/display/draw/drawData/DrawData.h"
#include "class/display/texture/Texture.h"
class Shader2D;
class DrawTexture{
public:
	DrawTexture(Texture *tex,DrawData* data);
	virtual ~DrawTexture();
	void draw(Shader2D *shader);
	DrawData* data;
	Texture *tex;
};

#endif /* DRAWTEXTURE_H_ */
