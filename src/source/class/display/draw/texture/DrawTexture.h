#ifndef DRAWTEXTURE_H_
#define DRAWTEXTURE_H_
class Shader;
class DrawTexture{
public:
	DrawTexture();
	virtual ~DrawTexture();
	virtual void draw_texture(Shader *shader)=0;
};

#endif /* DRAWTEXTURE_H_ */
