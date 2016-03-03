#version 400 core

#include <files/shader/header/commondata.verth>
uniform float waveTime;

out float height;

float gen_water_height(float waveWidth,float waveHeight){
	float x=vertout.position.x/waveWidth;
	float z=vertout.position.z/waveWidth;
	float height=0.0f;

	height+=0.2*sin((0.7*x+0.3*z)/1.0+1.0*waveTime);
	height+=0.2*sin(0.3*(0.4*x+0.6*z)/0.7+1.0*waveTime);
	height+=0.15*sin(0.3*(0.2*x+0.8*z)/0.4+1.5*waveTime+0.5);
	height+=0.15*sin(0.3*(0.6*x+0.4*z)/0.3+1.8*waveTime+0.3);
	height+=0.1*sin(0.3*(0.5*x+0.5*z)/0.2+2.2*waveTime);
	height+=0.1*sin(0.3*(0.9*x+0.1*z)/0.2+2.5*waveTime);
	height+=0.1*sin(0.3*(0.3*x+0.7*z)/0.15+3.0*waveTime);
	height-=1.0f;
	height*=waveHeight;
	return height;
}
void main(){ 	
	//common_vert();
	

	vertout.vertexPosition=vertexPosition;

	vertout.position=M*vec4(vertout.vertexPosition,1);//real world position
	height=gen_water_height(3.0f,0.2f);
	vertout.position.y+=height;
	vertout.MVP_pos=VP*vertout.position; 
 	vertout.Normal=(M*vec4(vertexNormal,0)).xyz;
    vertout.UV=vertexUV;
    gl_Position=vertout.MVP_pos;
}