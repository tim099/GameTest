#version 400 core

in vec2 UV;

layout(location = 0)out vec4 color;

uniform sampler2D myTextureSampler;
uniform float alpha;

void main(){ 
	vec3 temp_color=texture(myTextureSampler,UV).xyz;
    color=vec4(temp_color,alpha);
}