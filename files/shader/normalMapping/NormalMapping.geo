#version 400 core

layout(triangles)in;
layout(triangle_strip,max_vertices=3)out;

in VertexDataOut {
	vec2 UV;
	vec3 Normal;
	vec3 vertexPosition;
	vec4 position;
	vec4 MVP_pos;
}vertin[3];

out VertexData{
	vec2 UV;
	vec3 Normal;
	vec4 position;
	vec4 MVP_pos;
	vec3 T;
	vec3 B;
}vert;
uniform mat4 M; 
void main(){
    vec3 dPos1=(vertin[1].vertexPosition)-(vertin[0].vertexPosition);
    vec3 dPos2=(vertin[2].vertexPosition)-(vertin[0].vertexPosition);

 	vec2 dUV1=vertin[1].UV-vertin[0].UV;
    vec2 dUV2=vertin[2].UV-vertin[0].UV;
    float val=(dUV1.x*dUV2.y-dUV1.y*dUV2.x);
    if(abs(val)<0.00001f)val=0.00001f;
	float r=1.0f/val;
	
	vec3 T=(M*vec4((dPos1*dUV2.y-dPos2*dUV1.y)*r,0)).xyz;//
	vec3 B=(M*vec4((dPos2*dUV1.x-dPos1*dUV2.x)*r,0)).xyz;//

	for(int i=0;i<3;i++){
		gl_Position=gl_in[i].gl_Position;
		vert.UV=vertin[i].UV;
		vert.Normal=vertin[i].Normal;
		vert.position=vertin[i].position;
		vert.MVP_pos=vertin[i].MVP_pos;
		vert.T=T;
		vert.B=B;
		EmitVertex();
	}
	EndPrimitive();
} 