#ifndef RENDERER_H_
#define RENDERER_H_
#include "class/tim/Thread/Thread.h"
#include "class/display/texture/texture3D/Texture2DArr/Texture2DArr.h"
#include "class/display/texture/texture3D/cubemap/TextureCubeMap.h"
#include "class/display/texture/TextureMap.h"

class Shader;
class Shader2D;
class FrameBuffer;
class Camera;
class LightControl;
class Draw;
class Window;
class Mouse;
class Renderer{

public:
	Renderer(LightControl* lightControl,Draw *d_obj,Window *window,
			Camera *camera,Mouse* mouse,TextureMap *texmap,double* shadow_dis);
	virtual ~Renderer();
	bool Rendering()const;
	void render();
	void set_window(Window *window);
	void switch_shader(std::string name);
	FrameBuffer *FBO,*FBO2;
protected:
	void creat_shaders();
	/*
	 * use FBO depth buffer data to get mouse position in world position
	 */
	void update_mouse_data();
	TextureMap *texmap;
	Shader *shader;

	Camera *camera;
	Shader2D *shader2D;
	LightControl* lightControl;


	Draw *d_obj;

	Window *window;
	Mouse* mouse;//update 3d pos
	std::vector<Shader*>shaders;
	GLuint VertexArrayID;
	double* shadow_dis;
	bool rendering;
};

#endif /* RENDERER_H_ */
