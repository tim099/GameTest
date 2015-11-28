#ifndef RENDERER_H_
#define RENDERER_H_
#include "class/tim/Thread/Thread.h"
#include "class/display/texture/texture3D/Texture2DArr.h"
#include "class/display/texture/TextureMap.h"
class Shader;
class FrameBuffer;
class Camera;
class LightControl;
class Draw;
class Window;
class Mouse;
class Renderer{

public:
	Renderer(LightControl* lightControl,Draw *d_obj,Window *window,Shader **shader,FrameBuffer *FBO,
			Camera *camera,Mouse* mouse,TextureMap *texmap,double* shadow_dis);
	virtual ~Renderer();
	bool Rendering()const;
	void render();
protected:
	Texture *texarr;
	TextureMap *texmap;
	Shader **shader;
	FrameBuffer *FBO;
	Camera *camera;
	Shader *shader2D;
	LightControl* lightControl;
	Draw *d_obj;
	Window *window;
	Mouse* mouse;//update 3d pos
	double* shadow_dis;
	bool rendering;
};

#endif /* RENDERER_H_ */
