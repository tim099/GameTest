#include "class/display/model/modelBuffer/ModelBuffer.h"
#include "class/display/buffer/Buffer.h"
#include "class/display/model/Model.h"
#include "class/display/texture/Texture.h"
#include "class/display/shader/Shader.h"
#include <iostream>
namespace Display{
ModelBuffer::ModelBuffer(Model *m) {
	initialize(m);
}
ModelBuffer::ModelBuffer(std::string model_path, float size,
		bool align_center) {
	Model*m = Model::load_obj(model_path.c_str(), size, align_center);
	initialize(m);
	delete m;
}
void ModelBuffer::initialize(Model *m) {
	vtbuffer = 0;
	uvbuffer = 0;
	vnbuffer = 0;
	lybuffer = 0;
	load_model(m);
}
ModelBuffer::~ModelBuffer() {
	delete vtbuffer;
	delete uvbuffer;
	delete vnbuffer;
	if (lybuffer)
		delete lybuffer;
	//std::cout << "delete model buffer" << std::endl;
}
void ModelBuffer::load_model(Model *m) {
	if (!vtbuffer) {
		vtbuffer = new Buffer(m->vtBuffer, m->vtdatasize(), 0, 3, GL_FLOAT);
	} else {
		vtbuffer->update_buffer(m->vtBuffer, m->vtdatasize());
	}
	if (!uvbuffer) {
		uvbuffer = new Buffer(m->uvBuffer, m->uvdatasize(), 1, 2, GL_FLOAT);
	} else {
		uvbuffer->update_buffer(m->uvBuffer, m->uvdatasize());
	}
	if (!vnbuffer) {
		vnbuffer = new Buffer(m->vnBuffer, m->vndatasize(), 2, 3, GL_FLOAT);
	} else {
		vnbuffer->update_buffer(m->vnBuffer, m->vndatasize());
	}

	if (m->lyBuffer) {
		if (!lybuffer) {
			lybuffer = new Buffer(m->lyBuffer, m->lydatasize(), 3, 1, GL_FLOAT);
		} else {
			lybuffer->update_buffer(m->lyBuffer, m->lydatasize());
		}
	} else {
		if (!lybuffer) {
			lybuffer = 0;
		} else {
			delete lybuffer;
			lybuffer = 0;
		}
	}
	vertex_num = m->vtlen();
}
void ModelBuffer::bind_buffer(Shader *shader) {
	vtbuffer->bind_buffer();
	uvbuffer->bind_buffer();
	vnbuffer->bind_buffer();

	if (lybuffer) {
		lybuffer->bind_buffer();
		shader->Enable(Shader::LayerTexture); //enable lybuffer
	} else {
		shader->Disable(Shader::LayerTexture); //disable lybuffer
	}
}
void ModelBuffer::unbind_buffer(Shader *shader) {
	if (lybuffer)
		lybuffer->unbind_buffer();
	//vtbuffer->unbind_buffer();
	//uvbuffer->unbind_buffer();
	//vnbuffer->unbind_buffer();
}
void ModelBuffer::draw(GLuint programID, GLenum mode) {
	//std::cout<<"ModelBuffer::draw="<<vertex_num<<std::endl;
	glDrawArrays(mode, 0, vertex_num);
	//std::cout<<"ModelBuffer::draw end"<<std::endl;
	//glDrawArrays(GL_LINES,0,vertex_num);
	//glDrawArrays(GL_POINTS,0,vertex_num);
}
}
