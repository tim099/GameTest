#ifndef MODEL_H_
#define MODEL_H_
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <vector>
class Obj;
class Model {
public:
	Model(int max_len=0);
	Model(Obj* obj);
	virtual ~Model();

	static Model* load_obj(const char* path,GLfloat size,bool translate_to_o=true);

	void clear();

	void translate_to_o();
	int vtdatasize()const;
	int uvdatasize()const;
	int vndatasize()const;
	int vtlen()const;
	int uvlen()const;
	int vnlen()const;
	void translate(glm::vec3 v);
	void scale(GLfloat size);
	void merge(Model *m,glm::vec3 trans);
	void max_len_alter(int _len);
	GLfloat* vtBuffer;
	GLfloat* uvBuffer;
	GLfloat* vnBuffer;
	glm::vec4 mat;
	int len,max_len;
protected:

	void initial(int len,int max_len);
	void check_size();
	glm::vec3 msize;
	glm::vec3 mpos;

};

#endif /* MODEL_H_ */
