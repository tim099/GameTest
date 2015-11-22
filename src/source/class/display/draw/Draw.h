#ifndef DRAW_H_
#define DRAW_H_
#include <vector>
#include "class/display/draw/DrawObject.h"
#include "class/display/draw/texture/DrawTexture.h"
class Draw {
public:
	Draw();
	virtual ~Draw();
	void draw(Shader *shader);
	void draw_shadow(Shader *shader);
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
};

#endif /* DRAW_H_ */
