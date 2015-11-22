#version 400 core

layout(location = 0)in vec3 vertexPosition;

uniform mat4 LVP;
uniform mat4 M; 

void main(){ 
	gl_Position=LVP*M*vec4(vertexPosition,1);
}