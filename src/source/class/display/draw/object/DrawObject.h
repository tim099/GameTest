#ifndef DRAWOBJECT_H_
#define DRAWOBJECT_H_
#include <vector>
#include <class/display/buffer/BufferObject.h>
#include <class/tim/math/Position.h>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include "class/display/draw/object/drawData/DrawDataObj.h"
class Texture;
class Shader;
class DrawObject {
public:
	DrawObject(BufferObject* obj,Texture* texture=0,Texture* NormalMap=0,bool layer_texture=false);
	virtual ~DrawObject();
	//static glm::mat4 model_matrix(Position* p);
	static void Model_veiw(GLuint programID,const glm::mat4 &model_matrix);
	virtual void draw_object(Shader *shader);
	virtual void draw_shadow_map(Shader *shader);
	//update draw object if neccessary
	virtual void update();

	unsigned temp_pos_num()const;
	void push_drawdata(DrawDataObj* data);
	void push_temp_drawdata(DrawDataObj* data);
	void set_obj(BufferObject *obj);
	void clear_drawdata();
	void clear_temp_drawdata();
	bool draw_shadow;
protected:
	bool layer_texture;
	BufferObject *obj;
	Texture* texture;
	Texture* NormalMap;
	void draw_vec(Shader *shader,std::vector<DrawDataObj*> &data_v);
	void draw_shadow_vec(Shader *shader,std::vector<DrawDataObj*> &data_v);
	std::vector<DrawDataObj*>datas;
	std::vector<DrawDataObj*>temp_datas;

};

#endif /* DRAWOBJECT_H_ */
