#ifndef UNIFORM_H_
#define UNIFORM_H_
#include <glm/glm.hpp>
#include <GL/glew.h>
#include <string>
class Uniform {
public:
	Uniform();
	virtual ~Uniform();
	static void sentMat4Arr(GLuint programID,glm::mat4* MatArr,int num,std::string name);
	static void sentUniform(GLuint programID,std::string name,glm::vec3 pos);
	static void sentUniform(GLuint programID,std::string name,glm::vec2 pos);
	static void sentUniform(GLuint programID,std::string name,GLfloat val);
	static void printMat4(glm::mat4& Mat);
};

#endif /* UNIFORM_H_ */
