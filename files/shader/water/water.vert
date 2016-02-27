#version 400 core

#include <files/shader/header/commondata.verth>
uniform float waveTime;

out float height;

float gen_water_height(float waveWidth,float waveHeight){
	float height=sin(0.3*waveWidth*vertout.position.x+1.5*waveTime) 
		*cos(0.3*waveWidth*vertout.position.z+1.5*waveTime)*0.25f*waveHeight;
	height+=cos(0.5*waveWidth*vertout.position.x+1.1*waveTime+0.3) 
		* sin(0.5*waveWidth * vertout.position.z + 1.1*waveTime+0.3)*0.25f*waveHeight;
	height+=cos(0.7*waveWidth*vertout.position.x+0.7*waveTime+0.5) 
		* sin(0.7*waveWidth * vertout.position.z + 0.7*waveTime+0.5)*0.25f*waveHeight;
	height+=cos(waveWidth*vertout.position.x+0.4*waveTime+0.7) 
		* sin(waveWidth * vertout.position.z + 0.4*waveTime+0.7)*0.25f*waveHeight;
	return height;
}
void main(){ 	
	//common_vert();
	
	//float waveTime=0.3f;
	//float waveWidth=0.3f;
	//float waveHeight=0.5f;
	vertout.vertexPosition=vertexPosition;

	vertout.position=M*vec4(vertout.vertexPosition,1);//real world position
	height=gen_water_height(0.3f,0.5f);
	vertout.position.y+=height;
	vertout.MVP_pos=VP*vertout.position; 
 	vertout.Normal=(M*vec4(vertexNormal,0)).xyz;
    vertout.UV=vertexUV;
    gl_Position=vertout.MVP_pos;
}