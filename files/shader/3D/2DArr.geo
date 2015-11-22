#version 400 core

layout(triangles)in;
layout(triangle_strip,max_vertices=18)out;

in VertexData{
    vec2 UV;
}vertout[3];

out VertexData{
    vec2 UV;
}vert;

void main(){
	for(int i=0;i<3;i++){
		gl_Position=gl_in[i].gl_Position;
		vert.UV=vertout[i].UV;
		EmitVertex();
	}
	EndPrimitive();

}  