#ifndef BUFFEROBJECT_H_
#define BUFFEROBJECT_H_
#include <GL/glew.h>
#include <glm/glm.hpp>
#include "class/display/buffer/Buffer.h"
class Model;
class Shader;
class BufferObject{
public:
	BufferObject(Model *m,bool auto_delete=true);
	virtual ~BufferObject();
	void bind_buffer(Shader *shader);
	void draw(GLuint programID,GLenum mode=GL_TRIANGLES);
	bool AutoDelete()const;

	int vertex_num;
	Buffer *vtbuffer;
	Buffer *uvbuffer;
	Buffer *vnbuffer;
	Buffer *lybuffer;
	glm::vec4 mat;
	bool enable_lybuffer;
private:
	bool auto_delete;
};

#endif /* BUFFEROBJECT_H_ */
