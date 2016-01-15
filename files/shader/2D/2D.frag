#version 400 core
#include <files/shader/header2D/option>
#include <files/shader/header2D/commondata2D.fragh>


void main(){ 
	vec3 temp_color=get_color();
	
	if((shaderData&AddOnMode)!=0){
		color=vec4(temp_color,length(temp_color));
	}else{
		color=vec4(temp_color,alpha);
	}
    
}