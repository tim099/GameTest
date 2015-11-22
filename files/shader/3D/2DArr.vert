#version 400 core

layout(location=0) in vec3 vertexPosition;


out VertexData {
    vec2 UV;
}vertout;

uniform float size;
uniform vec3 position;
void main(){ 
    gl_Position=vec4(size*vertexPosition+position,1);  //size* 
    vertout.UV = vec2(0.5*vertexPosition.x+0.5,0.5*vertexPosition.y+0.5);//texture UV range 0.0~1.0
}