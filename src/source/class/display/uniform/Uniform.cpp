#include "class/display/uniform/Uniform.h"
#include "class/tim/string/String.h"
#include <cstdio>
Uniform::Uniform() {

}
Uniform::~Uniform() {

}
void Uniform::sentMat4Arr(GLuint programID,glm::mat4* MatArr,int num,std::string name){
	//Tim::String::gen_array_num(name,0);
	GLuint UNI=glGetUniformLocation(programID,name.c_str());
	for(int i=0;i<num;i++){
		glUniformMatrix4fv(UNI+i,1,GL_FALSE,&((MatArr[i])[0][0]));
	}
}
void Uniform::printMat4(glm::mat4& Mat){
	for(int i=0;i<4;i++){
		for(int j=0;j<4;j++){
			printf("%lf ",Mat[j][i]);
		}
		printf("\n");
	}
}
