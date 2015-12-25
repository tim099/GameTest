#version 400 core

#include <files/shader/header/commondata.fragh>
#include <files/shader/header/toon.fragh>

//layout(location = 1)out vec3 color2;
uniform samplerCube cubetex;
void main(){ 
	vec3 tex_color=get_tex_color();
	vec3 Normal=get_normal();
	
    vec3 total_light=compute_total_light(Normal,vert.position);
    
 	//color = vec4(toon((total_light)*tex_color,5.0f),1.0);
 	
 	
 	//color=vec4(Normal,1.0);
 	//vec3 lvec=-(camera_pos-vert.position.xyz);
    //vec3 vect=lvec-2*(lvec-dot(lvec,normalize(Normal))*normalize(Normal));
    //vec3 reflect_color=texture(cubetex,normalize(vect)).xyz;

 	//color=vec4(cross(normalize(camera_pos-vert.position.xyz),Normal),1.0);//+reflect_color
	color=vec4((total_light)*tex_color,1.0);//+reflect_color
	
	

}