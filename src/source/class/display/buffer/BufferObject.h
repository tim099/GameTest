#ifndef BUFFEROBJECT_H_
#define BUFFEROBJECT_H_
#include <GL/glew.h>
#include <glm/glm.hpp>

class Model;
class BufferObject{
public:
	BufferObject(GLuint vtbuffer,GLuint uvbuffer,GLuint texturebuffer,GLuint nbuffer,int vertex_num
			,glm::vec4 mat);
	BufferObject(Model *m,bool auto_delete=true);
	virtual ~BufferObject();
	void bind_buffer(GLuint programID);
	void draw(GLuint programID);
	bool AutoDelete()const;
	int vertex_num;
	GLuint vtbuffer;
	GLuint uvbuffer;
	GLuint vnbuffer;
	glm::vec4 mat;

private:
	bool auto_delete;
};

#endif /* BUFFEROBJECT_H_ */
