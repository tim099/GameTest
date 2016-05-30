#version 400 core

#include <files/shader/header2D/commondata2D.fragh>


void main(){ 
	vec3 temp_color=get_color();
	float a=get_alpha(temp_color);

    color=vec4(temp_color,a);
}