#ifndef DRAW_H_
#define DRAW_H_
#include <vector>
#include "class/display/draw/object/DrawObject.h"
#include "class/display/draw/texture/DrawTexture.h"
#include "class/tim/thread/mutex/Mutex.h"
class Draw {
public:
	Draw();
	virtual ~Draw();
	//render all object
	void draw(Shader *shader,Shader *shader2D);
	//render shadow map
	void draw_shadow(Shader *shader);
	//update all object
	void update();
	//update all draw object
	void remove(DrawObject* obj);
	void push(DrawObject* obj);
	void push(DrawTexture* tex);
	unsigned obj_size()const;
	void clear_tmp_pos();
	DrawObject* get_obj(unsigned i);
protected:
	std::vector<DrawObject*>d_objs;
	std::vector<DrawTexture*>d_texs;
	std::vector<Draw*>subdraw;


	Tim::Mutex* d_objsMutex;
	Tim::Mutex* d_texsMutex;
};

#endif /* DRAW_H_ */
