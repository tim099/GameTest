#version 400 core

#include <files/shader/header/commondata.verth>

void main(){ 	
	vertout.vertexPosition=vertexPosition;
	vertout.position=M*vec4(vertexPosition,1);//real world pos
	vertout.MVP_pos=VP*vertout.position; 
    gl_Position=vertout.MVP_pos;   
 	vertout.Normal=(M*vec4(vertexNormal,0)).xyz;
    vertout.UV = vertexUV;
}