#version 400 core

#include <files/shader/header/commondata.verth>
#include <files/shader/water/water>



out float _waveWidth;
out float _waveHeight;
uniform float waveHeight;
uniform float waveWidth;
void main(){ 	
	//common_vert();
	

	vertout.vertexPosition=vertexPosition;

	vertout.position=M*vec4(vertout.vertexPosition,1);//real world position
	_waveWidth=waveWidth;
	_waveHeight=waveHeight;
	float height=gen_water_height(vec2(vertout.position.x,vertout.position.z)
		,_waveWidth,_waveHeight);
	vertout.position.y+=height;
	vertout.MVP_pos=VP*vertout.position; 
 	vertout.Normal=(M*vec4(vertexNormal,0)).xyz;
    vertout.UV=vertexUV;
    gl_Position=vertout.MVP_pos;
}