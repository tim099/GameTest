#version 400 core

#include <files/shader/header/commondata.fragh>
#include <files/shader/header/toon.fragh>

void main(){ 
	vec3 tex_color=get_tex_color();
	vec3 Normal=vert.Normal;
	
    vec3 total_light=compute_total_light(Normal,vert.position);

    vec3 reflect_color=get_reflect(Normal);
    //vec3 refract_color=get_refract(Normal,1.0/1.3);
 	
 	//color = vec4((total_light+get_skybox()),1.0);
 	//color = vec4(toon((total_light)*tex_color,5.0f),1.0);
 	//color = vec4(total_light*tex_color,1.0);	
 	color = vec4(total_light*tex_color+reflect_color,1.0);
 	
 	//color=vec4(vert.Normal,1.0);

}