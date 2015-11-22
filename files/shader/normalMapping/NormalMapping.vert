#version 400 core

layout(location = 0) in vec3 vertexPosition;
layout(location = 1) in vec2 vertexUV;
layout(location = 2) in vec3 vertexNormal;

uniform mat4 VP;
uniform mat4 M; 

out VertexDataOut {
	vec2 UV;
	vec3 Normal;
	vec3 vertexPosition;
	vec4 position;
	vec4 MVP_pos;
}vertout;

void main(){ 	
	vertout.vertexPosition=vertexPosition;
	vertout.position=M*vec4(vertexPosition,1);//real world pos
	vertout.MVP_pos=VP*vertout.position; 
    gl_Position=vertout.MVP_pos;   
 	vertout.Normal=(M*vec4(vertexNormal,0)).xyz;
    vertout.UV = vertexUV;
}