#ifndef BUFFER_H_
#define BUFFER_H_
#include <GL/glew.h>
namespace Display{
class Buffer {
public:
	Buffer(GLfloat* data,int datasize,GLuint index,GLint size,GLenum type
			,GLboolean normalized=GL_FALSE
			,GLsizei stride=0);
	virtual ~Buffer();
	static GLuint gen_buffer(GLfloat* data,int datasize);
	static GLuint GenVertexArray();

	static void bind_vtbuffer(GLuint vertexbuffer);
	static void bind_uvbuffer(GLuint uvbuffer);
	static void bind_vnbuffer(GLuint vnbuffer);
	static void disable_all_buffer();
	void update_buffer(GLfloat* data,int datasize);
	void bind_buffer();
	void unbind_buffer();
protected:
	GLuint buffer;
	GLuint index;
	GLint size;
	GLenum type;
	GLboolean normalized;
	GLsizei stride;
};
}
#endif /* BUFFER_H_ */
