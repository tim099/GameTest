#ifndef BUFFEROBJECT_H_
#define BUFFEROBJECT_H_
#include <GL/glew.h>
#include <glm/glm.hpp>
#include "class/display/buffer/Buffer.h"
#include <string>


namespace Display{
class Model;
class Shader;
class ModelBuffer{
public:
	ModelBuffer(Model *m);
	ModelBuffer(std::string model_path,float size,bool align_center=true);
	void initialize(Model *m);
	virtual ~ModelBuffer();

	void load_model(Model *m);

	void bind_buffer(Shader *shader);
	void unbind_buffer(Shader *shader);
	void draw(GLuint programID,GLenum mode=GL_TRIANGLES);

	int vertex_num;
	Buffer *vtbuffer;
	Buffer *uvbuffer;
	Buffer *vnbuffer;
	Buffer *lybuffer;
	//bool enable_lybuffer;
private:

};
}
#endif /* BUFFEROBJECT_H_ */
