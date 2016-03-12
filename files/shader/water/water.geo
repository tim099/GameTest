#version 400 core

#include <files/shader/header/commondata.geoh>

in float _waveWidth[3];
in float _waveHeight[3];


out float waveWidth;
out float waveHeight;
void main(){
	vec3 dPos1=(vertin[1].position.xyz)-(vertin[0].position.xyz);
    vec3 dPos2=(vertin[2].position.xyz)-(vertin[0].position.xyz);

	//vec3 N=vertin[i].Normal;
	//vec3 N=normalize(cross(dPos1,dPos2));
	for(int i=0;i<3;i++){
		gl_Position=gl_in[i].gl_Position;
		vert.UV=vertin[i].UV;
		vert.Normal=vertin[i].Normal;
		vert.position=vertin[i].position;
		vert.MVP_pos=vertin[i].MVP_pos;
		vert.UVlayer=vertin[i].UVlayer;
		waveWidth=_waveWidth[i];
		waveHeight=_waveHeight[i];
		
		EmitVertex();
	}
	EndPrimitive();
} 