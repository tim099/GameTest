#version 400 core

layout(location=0) in vec3 vertexPosition;

out vec2 UV;

void main(){ 
    gl_Position=vec4(vertexPosition,1);   
    UV = vec2(0.5*vertexPosition.x+0.5,0.5*vertexPosition.y+0.5);//texture UV range 0.0~1.0
}