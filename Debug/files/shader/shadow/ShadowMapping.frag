#version 400 core
layout(location = 0)out float depth;
void main(){ 
	depth=gl_FragCoord.z/gl_FragCoord.w;
	//depth=0.9;
}