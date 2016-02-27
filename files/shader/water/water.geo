#version 400 core

#include <files/shader/header/commondata.geoh>

in float height[3];
void main(){
	vec3 dPos1=(vertin[1].position.xyz)-(vertin[0].position.xyz);
    vec3 dPos2=(vertin[2].position.xyz)-(vertin[0].position.xyz);

 	vec2 dUV1=vertin[1].UV-vertin[0].UV;
    vec2 dUV2=vertin[2].UV-vertin[0].UV;
    float val=(dUV1.x*dUV2.y-dUV1.y*dUV2.x);
    if(abs(val)<0.00001f)val=0.00001f;
	float r=1.0f/val;
	
	vec3 T=(M*vec4((dPos1*dUV2.y-dPos2*dUV1.y)*r,0)).xyz;//
	vec3 B=(M*vec4((dPos2*dUV1.x-dPos1*dUV2.x)*r,0)).xyz;//
	//vec3 N=vertin[i].Normal;
	vec3 N=normalize(cross(dPos1,dPos2));
	for(int i=0;i<3;i++){
		gl_Position=gl_in[i].gl_Position;
		vert.UV=vertin[i].UV;
		vert.Normal=N;
		vert.position=vertin[i].position;
		vert.MVP_pos=vertin[i].MVP_pos;
		vert.UVlayer=vertin[i].UVlayer;
		vert.T=T;
		vert.B=B;
		EmitVertex();
	}
	EndPrimitive();
} 