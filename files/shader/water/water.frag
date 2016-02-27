#version 400 core

#include <files/shader/header/commondata.fragh>
#include <files/shader/header/toon.fragh>


void main(){ 
	vec3 tex_color=vec3(0.5,1,1);//get_tex_color()
	vec3 Normal=vert.Normal;//get_normal()vec3(0,1,0)
	
    vec3 total_light=compute_total_light(Normal,vert.position);
    float water_alpha=0.8f;
	color=vec4((total_light)*(0.4*tex_color+0.4f*get_reflect(Normal)),water_alpha);//+reflect_color
}