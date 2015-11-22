#version 400 core
//#extension GL_EXT_texture_array : enable

in vec2 UV;
flat in int index;  

layout(location = 0)out vec4 color;

uniform sampler2D myTextureSampler;
uniform sampler2DArray myTextureArrSampler;
uniform float alpha;

void main(){ 
	//vec3 tex_color=texture2DArray(myTextureArrSampler,vec3(UV,index)).rgb;
	//vec3 tex_color=texture2DArray(myTextureArrSampler,vec3(UV,0)).rgb;
	vec3 tex_color=texture(myTextureArrSampler,vec3(UV,0)).rgb;
	vec3 tex_color2=texture(myTextureSampler,UV).xyz;
	vec3 temp_color=0.5*tex_color+0.5*tex_color2;
    color=vec4(temp_color,alpha);
}