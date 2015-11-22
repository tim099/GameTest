#ifndef VERTEX_H_
#define VERTEX_H_
#include <GL/glew.h>
#include <glm/glm.hpp>
class Vertex {
public:
	Vertex();
	virtual ~Vertex();
	static void gen_quad_vt(GLfloat* vtBuffer,glm::vec3 pos,glm::vec3 size,bool up);
	static void gen_quad_uv(GLfloat* uvBuffer);
	static void gen_vn(GLfloat* vtBuffer,GLfloat* vnBuffer);
	static void fill_vec3(GLfloat* vt,glm::vec3 v,int num=1);
	static void fill_vec2(GLfloat* vt,glm::vec2 v,int num=1);

};

#endif /* VERTEX_H_ */
