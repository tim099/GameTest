#version 400 core
#include <files/shader/header2D/option>

in vec2 UV;
flat in ivec2 size;
layout(location = 0)out vec4 color;

uniform sampler2D Texture;
uniform float alpha;
uniform vec2 sobel_dv;

vec3 sobel(vec2 dv){
	float val;
	
	float arr[9];
	
	for(int l=0;l<3;l++){
		for(int m=0;m<3;m++){
			arr[3*l+m]=length(texture(Texture,UV+vec2((l-1.0)/size.x,(m-1.0)/size.y)).xyz);
		}
	}
	
	float GX=-dv.y*arr[0]+dv.y*arr[2]-dv.x*arr[3]+dv.x*arr[5]-dv.y*arr[6]+dv.y*arr[8];
	float GY=-dv.y*arr[0]+dv.y*arr[6]-dv.x*arr[1]+dv.x*arr[7]-dv.y*arr[2]+dv.y*arr[8];
	
	val=sqrt(GX*GX+GY*GY);
	
	return vec3(val,val,val);

}
void main(){ 
	vec3 temp_color;
	
	
	if((shaderData&SobelMode)!=0){
		temp_color=sobel(sobel_dv);
	}else{
		temp_color=texture(Texture,UV).xyz;
	}
	
	if((shaderData&AddOnMode)!=0){
		color=vec4(temp_color,length(temp_color));
	}else{
		color=vec4(temp_color,alpha);
	}
    
}