#version 400 core
#define MAX_LVP 18 //
#define MAX_VERTICES 54 //=3*MAX_LVP
layout(triangles)in;
layout(triangle_strip,max_vertices=MAX_VERTICES)out;

//out int gl_Layer;

uniform mat4 LVP[MAX_LVP];
uniform mat4 M; 
uniform int LVP_num;

void main(){
	for(int n=0;n<LVP_num;n++){
		for(int i=0;i<3;i++){
			gl_Position=(LVP[n]*M*gl_in[i].gl_Position);//
			gl_Layer=n;
			EmitVertex();
		}
		EndPrimitive();
	}
	
}  