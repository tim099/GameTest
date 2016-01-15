#ifndef DRAWTEXTURE_H_
#define DRAWTEXTURE_H_
#include "class/display/texture/drawData/DrawData.h"
#include "class/display/texture/Texture.h"
class Shader;
class DrawTexture{
public:
	DrawTexture(Texture *tex,DrawData* data);
	virtual ~DrawTexture();
	void draw(Shader *shader);
	DrawData* data;
	Texture *tex;
};

#endif /* DRAWTEXTURE_H_ */
