#version 400 core

#include <files/shader/header/commondata.fragh>
#include <files/shader/header/toon.fragh>
#include <files/shader/water/water>

uniform sampler2D reflectdepthtex;
uniform sampler2D reflecttex;
uniform sampler2D refractdepthtex;
uniform sampler2D refracttex;
uniform int real_water;
uniform mat4 reflectWVP;
uniform mat4 refractWVP;
vec3 get_water_refract(vec3 Normal,float ratio){
    vec3 look_vec=(vert.position.xyz-camera_pos); 
    vec3 refract_vec=refract(look_vec,-normalize(Normal),ratio);
    refract_vec=normalize(refract_vec);
    //refract_vec.y*=-1;
    vec4 position=vert.position;
    vec4 WVPpos=biasMat*refractWVP*position;
    WVPpos.xyz/=WVPpos.w;
    vec2 uv=vec2(WVPpos.x,WVPpos.y);
    float del;
    float dis=length(look_vec);
    int i=0,dir=0;
    float val=0.05,cur_val=0;//*dis   ;    
    
    

    while(i<10){//&&abs(val)>0.001
    	del=WVPpos.z-texture(refractdepthtex,uv).x;
    	if(del<0){
			if(dir==1){
    			val*=0.55;
    		}
    		dir=0;
    		cur_val-=val;
    		position=vert.position+cur_val*vec4(refract_vec.x,refract_vec.y,refract_vec.z,0);
    	}else{
			if(dir==0){
    			val*=0.55;
    		}
    		dir=1;
    		cur_val+=val;
    		position=vert.position+cur_val*vec4(refract_vec.x,refract_vec.y,refract_vec.z,0);
    		break;
    	}	
    	
		WVPpos=biasMat*refractWVP*position;
		WVPpos.xyz/=WVPpos.w;
    	uv=vec2(WVPpos.x,WVPpos.y);
    	i++;
    }
    
    //float d=1.0-texture(refractdepthtex,uv).x;
    //float d2=1.0-WVPpos.z;
    //return 100*vec3(d,d,d);  
    if(uv.x>1.0){
    	uv.x=1.0;
    }
    if(uv.x<0){
    	uv.x=0;	
    }
    if(uv.y>1.0){
    	uv.y=1.0;
    }
    if(uv.y<0){
    	uv.y=0;
    }
    //return 0.05*(vec3(position.y,position.y,position.y)-vec3(30,30,30));
    //return refract_vec;
   	//return vec3(uv,0);
    return texture(refracttex,uv).xyz;
}
vec3 get_water_reflect(vec3 Normal){

    vec3 look_vec=(vert.position.xyz-camera_pos);
    
    vec3 reflect_vec=look_vec-2*(look_vec-dot(look_vec,normalize(Normal))*normalize(Normal));
    
    reflect_vec=normalize(reflect_vec);
    
    vec4 position=vert.position;
    vec4 WVPpos=biasMat*reflectWVP*position;
    WVPpos.xyz/=WVPpos.w;
    vec2 uv=vec2(WVPpos.x,WVPpos.y);
    float del;
    int i=0,dir=0;
    //float dis=length(look_vec);
    float val=3.5,cur_val=0;//*dis

    while(i<10){
    	del=WVPpos.z-texture(reflectdepthtex,uv).x;
    	if(del<0){
    		if(dir==1){
    			val*=0.55;
    		}
    		dir=0;
    		cur_val-=val;
    		position=vert.position+cur_val*vec4(reflect_vec.x,reflect_vec.y,reflect_vec.z,0);
    	}else{	
    		if(dir==0){
    			val*=0.55;
    		}
    		dir=1;
    		cur_val+=val;
    		position=vert.position+cur_val*vec4(reflect_vec.x,reflect_vec.y,reflect_vec.z,0);
    		break;
    	}
    	WVPpos=biasMat*reflectWVP*position;
    	WVPpos.xyz/=WVPpos.w;
    	uv=vec2(WVPpos.x,WVPpos.y);
    	i++;
    }

    if(uv.x>1.0){
    	//return 0.5*vec3(uv.x,0,0);
    	uv.x=1.0;
    }
    if(uv.x<0){
    	//return 0.5*vec3(0,1.0-uv.x,0);
    	uv.x=0;	
    }
    if(uv.y>1.0){
    	//return 0.5*vec3(uv.y,0,0);
    	uv.y=1.0;
    }
    if(uv.y<0){
    	//return 0.5*vec3(0,1.0-uv.y,0);
    	uv.y=0;
    }
    return texture(reflecttex,uv).xyz;
}
in float waveWidth;
in float waveHeight;
vec3 get_water_normal(){
	float del=0.003;
	float h=gen_water_height(vec2(vert.position.x,vert.position.z),waveWidth,waveHeight);
	float h1=gen_water_height(vec2(vert.position.x+del,vert.position.z),waveWidth,waveHeight);
	float h2=gen_water_height(vec2(vert.position.x,vert.position.z+del),waveWidth,waveHeight);
	vec3 v1=vec3(del,h1-h,0);
	vec3 v2=vec3(0,h2-h,del);
	return normalize(cross(v2,v1));
}
void main(){ 
	vec3 tex_color=vec3(0.4,0.75,1);//get_tex_color()
	vec3 Normal;

	Normal=get_water_normal();
	//Normal=vert.Normal;

    vec3 total_light=compute_total_light(Normal,vert.position);
    float water_alpha=1.0f;
    //vec3 reflect_col=get_reflect(Normal);
    //vec3 refract_col=get_refract(Normal,3.6);
    if(real_water!=0){
        vec3 reflect_col=get_water_reflect(Normal);
    	vec3 refract_col=get_water_refract(Normal,0.8);
		color=vec4((total_light)*(0.2*tex_color)+0.6f*reflect_col+0.4*refract_col,1.0);
    }else{
    	vec3 reflect_col=get_reflect(Normal);
    	color=vec4((total_light)*(0.4*tex_color+0.8f*reflect_col),0.7);
    }

}