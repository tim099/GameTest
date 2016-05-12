#include "class/display/shader/Shader.h"
#include "class/tim/string/String.h"
#include <iostream>
#include <glm/glm.hpp>
#include <fstream>
#include <vector>
#include <cstring>
#include <cstdio>
namespace Display{
Shader::Shader(std::string _name) {
	shaderData=0;
	programID=0;
	name=_name;
}
Shader::~Shader() {
	if(programID)glDeleteProgram(programID);
}
std::string Shader::Name()const{
	return name;
}
void Shader::EnableNormapping(){
	shaderData|=NormalMapping;
	sent_Uniform("shaderData",shaderData);
}
void Shader::DisableNormapping(){
	shaderData&=(~NormalMapping);
	sent_Uniform("shaderData",shaderData);
}
void Shader::Enable(int flag){
	shaderData|=flag;
	sent_Uniform("shaderData",shaderData);
}
void Shader::Disable(int flag){
	shaderData&=(~flag);
	sent_Uniform("shaderData",shaderData);
}
void Shader::sent_Uniform(std::string name,int i){
	glUniform1i(glGetUniformLocation(programID,name.c_str()),i);
}
void Shader::sent_Uniform(std::string name,glm::vec4 pos){
	glUniform4f(glGetUniformLocation(programID,name.c_str()),pos.x,pos.y,pos.z,pos.w);
}
void Shader::sent_Uniform(std::string name,glm::vec3 pos){
	glUniform3f(glGetUniformLocation(programID,name.c_str()),pos.x,pos.y,pos.z);
}
void Shader::sent_Uniform(std::string name,math::vec2<float> pos){
	glUniform2f(glGetUniformLocation(programID,name.c_str()),pos.x,pos.y);
}
void Shader::sent_Uniform(std::string name,float val){
	glUniform1f(glGetUniformLocation(programID,name.c_str()),val);
}
void Shader::sent_Uniform(std::string name,float x,float y){
	glUniform2f(glGetUniformLocation(programID,name.c_str()),x,y);
}
void Shader::active_shader(){
	glUseProgram(programID);
}
void Shader::read_shader(std::string &ShaderCode,const char* path){
    std::ifstream ShaderStream(path, std::ios::in);
    if(ShaderStream.is_open()){
    	ShaderCode="";
        std::string Line ="";
        while(getline(ShaderStream,Line)){
        	if(!Line.empty()){
            	if(Line.find(std::string("#include"))!=std::string::npos){
            		Line=Tim::String::cut(Line,std::string("#include"),true,true);
            		Line=Tim::String::cut(Line,std::string(" "),true,true);
            		Line=Tim::String::cut(Line,std::string("<"),true,true);
            		Line=Tim::String::cut(Line,std::string(">"),true,true);
            		//std::cout<<Line<<std::endl;
            		read_shader(Line,Line.c_str());
            		//std::cout<<Line<<std::endl;
            	}
            	ShaderCode+="\n"+Line;
        	}
        }
        ShaderStream.close();
    }else{
    	std::cout<<"load Shader:"<<path<<"false"<<std::endl;
    }
}
void Shader::compile_shader(GLuint ShaderID,std::string &ShaderCode){
    char const *SourcePointer=ShaderCode.c_str();
    glShaderSource(ShaderID,1,&SourcePointer,NULL);
    glCompileShader(ShaderID);
}
void Shader::check_shader(GLuint ShaderID,GLint &Result,int &InfoLogLength){
    glGetShaderiv(ShaderID,GL_COMPILE_STATUS,&Result);
    glGetShaderiv(ShaderID,GL_INFO_LOG_LENGTH,&InfoLogLength);
    std::vector<char> ShaderErrorMessage(InfoLogLength);
    glGetShaderInfoLog(ShaderID,InfoLogLength, NULL,&ShaderErrorMessage[0]);
    if(strcmp(&ShaderErrorMessage[0],""))fprintf(stdout, "%s\n", &ShaderErrorMessage[0]);
}
GLuint Shader::create_program(std::vector<GLuint> &shaders){
    GLuint ProgramID=glCreateProgram();
    for(unsigned i=0;i<shaders.size();i++){
    	glAttachShader(ProgramID,shaders.at(i));
    }
    glLinkProgram(ProgramID);
    check_program(ProgramID);
    return ProgramID;
}
void Shader::check_program(GLuint ProgramID){
	int InfoLogLength;
	GLint Result=GL_FALSE;
    glGetProgramiv(ProgramID,GL_LINK_STATUS,&Result);
    glGetProgramiv(ProgramID,GL_INFO_LOG_LENGTH,&InfoLogLength);
    std::vector<char> ProgramErrorMessage(InfoLogLength>1?InfoLogLength:1);
    glGetProgramInfoLog(ProgramID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
    if(strcmp(&ProgramErrorMessage[0],""))fprintf(stdout,"%s\n", &ProgramErrorMessage[0]);
}
GLuint Shader::create_shader(const char* src,GLenum type){
	GLuint ShaderID=glCreateShader(type);
    std::string ShaderCode;
    read_shader(ShaderCode,src);
    // Compile Shader
    compile_shader(ShaderID,ShaderCode);
    return ShaderID;
}
void Shader::LoadShader(const char* vertex,const char* fragment){
	std::vector<GLuint>shaders;
	shaders.push_back(create_shader(vertex,GL_VERTEX_SHADER));
	shaders.push_back(create_shader(fragment,GL_FRAGMENT_SHADER));

	GLuint ProgramID=create_program(shaders);
    programID=ProgramID;
}
void Shader::LoadShader(const char* vertex,const char* geometry,const char* fragment){
	std::vector<GLuint>shaders;
	shaders.push_back(create_shader(vertex,GL_VERTEX_SHADER));
	shaders.push_back(create_shader(fragment,GL_FRAGMENT_SHADER));
	shaders.push_back(create_shader(geometry,GL_GEOMETRY_SHADER));

	GLuint ProgramID=create_program(shaders);
    programID=ProgramID;
}
}
