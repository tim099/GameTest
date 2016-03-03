#version 400 core

#include <files/shader/header/commondata.fragh>
#include <files/shader/header/toon.fragh>
#include <files/shader/water/water>

uniform sampler2D scenedepthtex;

in float waveWidth;
in float waveHeight;
vec3 get_water_normal(){
	float del=0.003;
	float h=gen_water_height(vec2(vert.position.x,vert.position.z),waveWidth,waveHeight);
	float h1=gen_water_height(vec2(vert.position.x+del,vert.position.z),waveWidth,waveHeight);
	float h2=gen_water_height(vec2(vert.position.x,vert.position.z+del),waveWidth,waveHeight);
	vec3 v1=vec3(del,h1-h,0);
	vec3 v2=vec3(0,h2-h,del);
	return normalize(cross(v2,v1));
}
void main(){ 
	vec3 tex_color=vec3(0.4,0.75,1);//get_tex_color()
	//vec3 Normal=vert.Normal;//get_normal()vec3(0,1,0)
	vec3 Normal=get_water_normal();


    vec3 total_light=compute_total_light(Normal,vert.position);
    float water_alpha=0.85f;
    //color=vec4(Normal,1);
	color=vec4((total_light)*(0.4*tex_color+0.6f*get_reflect(Normal)),water_alpha);
	//mix(water_alpha,1.0,z_del)
}