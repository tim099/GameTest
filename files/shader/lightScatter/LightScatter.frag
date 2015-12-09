#version 400 core

#include <files/shader/header/commondata.fragh>


void main(){ 
	vec3 tex_color=get_tex_color();
	vec3 Normal=get_normal();
	
    vec3 total_light=compute_total_light(Normal,vert.position);
    
 	//color = vec4(toon((total_light)*tex_color,5.0f),1.0);
 	color = vec4(total_light*tex_color+light_scattering(vert.position),1.0);	
 	
 	//color=vec4(vert.Normal,1.0);

}