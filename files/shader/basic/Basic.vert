#version 400 core

layout(location = 0) in vec3 vertexPosition;
layout(location = 1) in vec2 vertexUV;
layout(location = 2) in vec3 vertexNormal;

out VertexData {
    vec2 UV;
    vec3 Normal;
    vec4 position;
}vertout;


uniform mat4 M; 
uniform mat4 VP;
void main(){ 
	vertout.position=M*vec4(vertexPosition,1);//real world pos
	vertout.Normal=(M*vec4(vertexNormal,0)).xyz;
    vertout.UV = vertexUV;
    gl_Position=VP*vertout.position;    
	//gl_Position=VP*vec4(vertout.position,1);
}