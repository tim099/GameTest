#ifndef RENDERER_H_
#define RENDERER_H_
#include "class/tim/Thread/Thread.h"

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
			Camera *camera,Mouse* mouse,double* shadow_dis);
	virtual ~Renderer();
	void render_all();
	bool Rendering()const;
protected:
	void render();
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
