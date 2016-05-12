#ifndef RENDERER_H_
#define RENDERER_H_
#include "class/tim/Thread/Thread.h"
#include "class/display/texture/texture3D/Texture2DArr/Texture2DArr.h"
#include "class/display/texture/texture3D/cubemap/TextureCubeMap.h"
#include "class/display/texture/AllTextures.h"


namespace Display{
class Shader;
class Shader2D;
class FrameBuffer;
class Camera;

class Window;
class Mouse;
class Draw;
class Renderer{

public:
	Renderer(Draw *d_obj,Window *window);
	virtual ~Renderer();
	bool Rendering()const;
	void render();
	void set_window(Window *window);

	void switch_shader(std::string name);
	FrameBuffer *FBO3D,*FBO2D,*waterReflectFBO,*waterRefractFBO;
protected:
	void creat_shaders();
	/*
	 * use FBO depth buffer data to get mouse position in world position
	 */
	Shader *shader;
	Shader *shaderWater;
	Shader *shaderShadowMapping;

	Shader2D *shader2D;

	Draw *draw;

	Window *window;
	std::vector<Shader*>shaders;
	GLuint VertexArrayID;
	bool rendering;
};
}
#endif /* RENDERER_H_ */
