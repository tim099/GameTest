#ifndef DRAW_H_
#define DRAW_H_
#include <vector>
#include <queue>
#include "class/display/draw/drawObject/DrawObject.h"
#include "class/display/draw/texture/DrawTexture.h"
#include "class/tim/thread/mutex/Mutex.h"
#include "class/tim/globalObject/GlobalObject.h"
class DrawData;
class RenderString;
class StringRenderer;
class LightControl;
class Shader;
class Camera;
class FrameBuffer;
class Draw: public Tim::GlobalObject<Draw> {
public:
	Draw();
	virtual ~Draw();

	void sent_shadow_uniform(Shader *shader);
	void gen_shadow();


	//render all object(3D Models)
	void draw3D(Shader *shader,FrameBuffer *FBO);
	/*
	 * draw all 2D object(texture,font...etc)
	 */
	void draw2D(Shader2D *shader2D,FrameBuffer *FBO);
	//render shadow map
	void draw_shadow(Shader *shader);
	//update all object
	void update();
	//update all draw object

	void remove(DrawObject* obj);
	void push(DrawObject* obj);
	void push(DrawTexture* tex);
	void push(RenderString* renderStr);
	DrawData* push_as_tex(RenderString* renderStr);

	void set_lightControl(LightControl* lightControl);
	void set_camera(Camera *camera);

	unsigned obj_size() const;
	void clear_tmp_data();
	DrawObject* get_obj(unsigned i);
	Camera *camera;
	bool Enable3D;
protected:

	LightControl* lightControl;

	std::vector<DrawObject*> d_objs;
	std::vector<DrawTexture*> d_texs;

	StringRenderer* strRenderer;

	Tim::Mutex* d_objsMutex;
	Tim::Mutex* d_texsMutex;
};

#endif /* DRAW_H_ */
