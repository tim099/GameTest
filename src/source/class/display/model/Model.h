#ifndef MODEL_H_
#define MODEL_H_
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <vector>
namespace Display{
class Obj;
class Model {
public:
	Model(int max_len=0,bool layertex=false);
	Model(Obj* obj);
	virtual ~Model();

	static Model* load_obj(const char* path,float size,bool align_center=true);

	void clear();

	void translate_to_o();
	int vtdatasize()const;
	int uvdatasize()const;
	int vndatasize()const;
	int lydatasize()const;
	int vtlen()const;
	int uvlen()const;
	int vnlen()const;
	int lylen()const;
	void translate(glm::vec3 v);
	void scale(float size);
	/*
	 * merge model and set the model layer of the model being merge
	 */
	void merge(Display::Model *m,glm::vec3 trans,float layer);
	/*
	 * merge model,can set the translate value of the model being merge
	 */
	void merge(Display::Model *m,glm::vec3 trans=glm::vec3(0,0,0));
	void max_len_alter(int _len);
	GLfloat* vtBuffer;
	GLfloat* uvBuffer;
	GLfloat* vnBuffer;
	GLfloat* lyBuffer;
	int vert_num,max_vert;
protected:

	void initial(int len,int max_len,bool layertex=false);
	void check_size();
	glm::vec3 msize;
	glm::vec3 mpos;

};
}
#endif /* MODEL_H_ */
