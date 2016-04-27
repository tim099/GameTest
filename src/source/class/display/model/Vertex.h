#ifndef VERTEX_H_
#define VERTEX_H_
#include <GL/glew.h>
#include <glm/glm.hpp>
namespace Display{
class Vertex {
public:
	Vertex();
	virtual ~Vertex();
	static void gen_quad_vt(GLfloat* vtBuffer,glm::vec3 pos,glm::vec3 size,bool up);
	/*
	 * a=left down corner of the UV,b=right up corner of the UV
	 */
	static void gen_quad_uv(GLfloat* uvBuffer,glm::vec2 a=glm::vec2(0,0),glm::vec2 b=glm::vec2(1,1));
	static void gen_vn(GLfloat* vtBuffer,GLfloat* vnBuffer);
	static void fill_vec3(GLfloat* vt,glm::vec3 v,int num=1);
	static void fill_vec2(GLfloat* vt,glm::vec2 v,int num=1);

};
}
#endif /* VERTEX_H_ */
