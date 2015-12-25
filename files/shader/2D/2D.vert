#version 400 core

layout(location=0) in vec3 vertexPosition;
layout(location = 1)in vec2 vertexUV;
out vec2 UV;
flat out ivec2 size;
uniform sampler2D Texture;

uniform vec2 position;
void main(){ 
	size=textureSize(Texture,0);
    gl_Position=vec4(vertexPosition+vec3(position,0),1);//
    UV=vertexUV;
}