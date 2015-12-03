#ifndef BUFFEROBJECT_H_
#define BUFFEROBJECT_H_
#include <GL/glew.h>
#include <glm/glm.hpp>
#include "class/display/buffer/Buffer.h"
class Model;
class BufferObject{
public:
	BufferObject(Model *m,bool auto_delete=true);
	virtual ~BufferObject();
	void bind_buffer(GLuint programID);
	void draw(GLuint programID);
	bool AutoDelete()const;

	int vertex_num;
	Buffer *vtbuffer;
	Buffer *uvbuffer;
	Buffer *vnbuffer;
	glm::vec4 mat;

private:
	bool auto_delete;
};

#endif /* BUFFEROBJECT_H_ */
