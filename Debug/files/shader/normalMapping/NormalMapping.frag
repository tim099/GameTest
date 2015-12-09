#version 400 core

#include <files/shader/header/commondata.fragh>
#include <files/shader/header/toon.fragh>

layout(location = 1)out vec3 color2;

void main(){ 
	vec3 tex_color=get_tex_color();
	vec3 Normal=get_normal();

    vec3 total_light=compute_total_light(Normal,vert.position);
    
 	//color = vec4(toon((total_light)*tex_color,5.0f),1.0);
 	
 	
 	//color=vec4(vert.Normal,1.0);

	color = vec4((total_light)*tex_color,1.0);
	//color2=vert.Normal;
	float dpc=(1.0/vert.MVP_pos.w)*vert.MVP_pos.z;//test
	while(dpc<0.05)dpc+=0.05;
	while(dpc<10.0)dpc*=2.0;

	dpc=(dpc-floor(dpc));
	color2=dpc*vec3(1.0,1.0,1.0);
}