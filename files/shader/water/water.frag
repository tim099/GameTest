#version 400 core

#include <files/shader/header/commondata.fragh>
#include <files/shader/header/toon.fragh>
#include <files/shader/water/water>

uniform sampler2D scenedepthtex;
uniform sampler2D reflecttex;

vec3 get_water_refract(vec3 Normal,float ratio){
    vec3 look_vec=(vert.position.xyz-camera_pos); 
    vec3 refract_vec=refract(look_vec,normalize(Normal),ratio); 
     
    return texture(skybox,normalize(refract_vec)).xyz;
    //return texture(scenecolortex,vec2()).xyz;
}
vec3 get_water_reflect(vec3 Normal){

    vec3 look_vec=(vert.position.xyz-camera_pos);
    vec3 reflect_vec=look_vec-2*(look_vec-dot(look_vec,normalize(Normal))*normalize(Normal));
    reflect_vec=normalize(reflect_vec);
    //return texture(reflecttex,vec2(0.5*reflect_vec.x+0.5,-0.5*reflect_vec.y+0.5)).xyz;
    
    return texture(reflecttex,vec2(0.5*vert.MVP_pos.x/vert.MVP_pos.w+0.5,
    0.5*vert.MVP_pos.y/vert.MVP_pos.w+0.5)).xyz;
}
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
    vec3 reflect_col=get_reflect(Normal);
    //vec3 reflect_col=get_water_reflect(Normal);
	color=vec4((total_light)*(0.4*tex_color+0.6f*reflect_col),water_alpha);
	//mix(water_alpha,1.0,z_del)
}