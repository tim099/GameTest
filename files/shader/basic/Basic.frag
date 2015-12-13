#version 400 core

#include <files/shader/header/commondata.fragh>

uniform samplerCube cubetex;
void main(){ 
	vec3 tex_color=get_tex_color();
	vec3 Normal=vert.Normal;
	
    vec3 total_light=compute_total_light(Normal,vert.position);
    
    
     
    vec3 lvec=(vert.position.xyz-camera_pos);
    vec3 vect=lvec-2*(lvec-dot(lvec,normalize(Normal))*normalize(Normal));
    
    float ratio = 1.00/1.3;
    vec3 R=refract(lvec,normalize(Normal),ratio);    
    //vec3 reflect_color=texture(cubetex,normalize(R)).xyz;
    vec3 reflect_color=texture(cubetex,normalize(vect)).xyz;
    
    
    //color=vec4(reflect_color,1.0);
    
    color=vec4(total_light*tex_color+reflect_color,1.0);

    //float dval=texture(cubedepthMap[0],normalize(vect)).x;
    //if(dval>0.999){
    	//color=vec4(vec3(0.5,0.5,0.5),1.0);
    //}else{
    	//color=vec4(total_light*tex_color+reflect_color,1.0);
    //}
    
    
 	
 	
 	//color=vec4(total_light*tex_color,1.0);
 	
 	//color = vec4(toon((total_light)*tex_color,5.0f),1.0);
 	//if(texture(cubedepthMap,vec3(vert.UV,vert.UVlayer)).x==0.0){
 		//color=vec4(total_light*vec3(1.5,1,1),1);
 	//}else{
 		//color=vec4(total_light*vec3(0.5,1,1),1);
 	//}
 	
 	//color = vec4(total_light*tex_color,1.0);	
 	
 	
 	//color=vec4(vert.Normal,1.0);

}