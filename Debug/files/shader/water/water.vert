#version 400 core

#include <files/shader/header/commondata.verth>
uniform float waveTime;
void main(){ 	
	//common_vert();
	
	//float waveTime=0.3f;
	float waveWidth=0.3f;
	float waveHeight=0.4f;
	vertout.vertexPosition=vertexPosition;

	vertout.position=M*vec4(vertout.vertexPosition,1);//real world position
	vertout.position.y+=sin(waveWidth*vertout.position.x+waveTime) 
		* cos(waveWidth * vertout.position.y + waveTime) * waveHeight;
	vertout.MVP_pos=VP*vertout.position; 
 	vertout.Normal=(M*vec4(vertexNormal,0)).xyz;
    vertout.UV=vertexUV;
    gl_Position=vertout.MVP_pos;
}