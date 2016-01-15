#ifndef DRAWOBJECT_H_
#define DRAWOBJECT_H_
#include <vector>
#include <class/display/buffer/BufferObject.h>
#include <class/tim/math/Position.h>
#include <GL/glew.h>
#include <glm/glm.hpp>
class Texture;
class Shader;
class DrawObject {
public:
	DrawObject(BufferObject* obj,Texture* texture=0,Texture* NormalMap=0,bool layer_texture=false);
	virtual ~DrawObject();
	//static glm::mat4 model_matrix(Position* p);
	static void Model_veiw(GLuint programID,glm::mat4 model_matrix);
	virtual void draw_object(Shader *shader);
	virtual void draw_shadow_map(Shader *shader);
	//update draw object if neccessary
	virtual void update();

	unsigned temp_pos_num()const;
	void push_position(Position* p);
	void push_temp_position(Position* p);
	void set_obj(BufferObject *obj);
	void clear_position();
	void clear_temp_position();
	bool draw_shadow;
protected:
	bool layer_texture;
	BufferObject *obj;
	Texture* texture;
	Texture* NormalMap;
	void draw_vec(GLuint programID,std::vector<Position*> &pos_v);
	std::vector<Position*>m_pos;
	std::vector<Position*>temp_pos;

};

#endif /* DRAWOBJECT_H_ */
