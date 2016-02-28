#version 400 core

#include <files/shader/header/commondata.fragh>
#include <files/shader/header/toon.fragh>

uniform sampler2D scenedepthtex;
void main(){ 
	vec3 tex_color=vec3(0.4,0.75,1);//get_tex_color()
	vec3 Normal=vert.Normal;//get_normal()vec3(0,1,0)
	
	//float z_val=vert.MVP_pos.z/vert.MVP_pos.w;
	//vec2 t=vert.MVP_pos.xy/vert.MVP_pos.w;
	//t+=1.0f;
	//t/=2.0f;
	//float scene_z=texture(scenedepthtex,t).x;
	//float z_del=z_val-scene_z;

    vec3 total_light=compute_total_light(Normal,vert.position);
    float water_alpha=0.85f;
	color=vec4((total_light)*(0.4*tex_color+0.6f*get_reflect(Normal))
	,water_alpha);//mix(water_alpha,1.0,z_del)
}