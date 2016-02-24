#version 400 core

#include <files/shader/header/commondata.fragh>
#include <files/shader/header/toon.fragh>


void main(){ 
	vec3 tex_color=get_tex_color();
	vec3 Normal=get_normal();
	
    vec3 total_light=compute_total_light(Normal,vert.position);
    
	color=vec4((total_light)*tex_color,get_tex_alpha());//+reflect_color
}