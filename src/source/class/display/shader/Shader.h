#ifndef SHADER_H_
#define SHADER_H_
#include <vector>
#include <string>
#include <GL/glew.h>
const int NormalMappingActive=1<<0;
const int LayerTexture=1<<1;
class Shader {
public:
	Shader(std::string name=std::string("default"));
	virtual ~Shader();
	void LoadShader(const char* vertex,const char* fragment);
	void LoadShader(const char* vertex,const char* geometry,const char* fragment);
	void active_shader();
	void Enable(int flag);
	void Disable(int flag);
	void EnableNormapping();
	void DisableNormapping();
	void sent_Uniform1i(const char* name,int i);
	std::string Name()const;
	GLuint programID;
protected:
	static GLuint create_shader(const char* src,GLenum type);
	static void read_shader(std::string &ShaderCode,const char* path);
	static void check_shader(GLuint VertexShaderID,GLint &Result,int &InfoLogLength);
	static GLuint create_program(std::vector<GLuint>&shaders);
	static void check_program(GLuint ProgramID);
	static void compile_shader(GLuint ShaderID,std::string &ShaderCode);
	int shaderData;
	std::string name;
};

#endif /* SHADER_H_ */
