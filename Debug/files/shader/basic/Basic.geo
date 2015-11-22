#version 400 core

layout(triangles)in;
layout(triangle_strip,max_vertices=6)out;

in VertexData{
    vec2 UV;
    vec3 Normal;
    vec4 position;
}vertout[3];

out VertexData{
    vec2 UV;
    vec3 Normal;
    vec4 position;
}vert;

uniform mat4 VP;
void main(){
	for(int i=0;i<3;i++){
		gl_Position=gl_in[i].gl_Position;
		vert.UV=vertout[i].UV;
		vert.Normal=vertout[i].Normal;
		vert.position=vertout[i].position;
		EmitVertex();
	}
	EndPrimitive();

}  