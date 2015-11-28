#version 400 core
#define MAX_LIGHT 100 

in VertexData {
    vec2 UV;
    vec3 Normal;
    vec4 position;
}vert;

layout(location = 0)out vec4 color;

uniform sampler2D myTextureSampler;

uniform vec3 camera_pos;

uniform vec4 mat;
uniform mat4 VP;

#include <files/shader/header/light/light>

uniform sampler2DArray testarr;
void main(){ 
	//vec3 tex_color=(texture(depthMap[1],vert.UV).rgb);
	
	//vec3 tex_color=(texture(myTextureSampler,vert.UV).rgb);
	vec3 tex_color=texture(testarr,vec3(vert.UV,1)).xyz;
	
	vec3 total_light=compute_total_light(vert.Normal,vert.position);
	
	
    color = vec4((total_light)*tex_color,1.0);
	
}