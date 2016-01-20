#include "class/display/light/shadow/ShadowData.h"
#include "class/display/texture/texture2D/Texture2D.h"
#include "class/display/texture/texture3D/Texture2DArr/Texture2DArr.h"
#include "class/display/texture/texture3D/cubemap/TextureCubeMap.h"
#include "class/display/shader/Shader.h"
#include "class/display/uniform/Uniform.h"
#include "class/display/shader/Shader.h"
#include <iostream>
#include <cstdio>
ShadowData::ShadowData(unsigned _max_l_shadow,unsigned _max_pl_shadow) {
	max_l_shadow=_max_l_shadow;
	max_pl_shadow=_max_pl_shadow;
	s_num=0;
	ps_num=0;

	LVP=new glm::mat4[max_l_shadow];
	PLVP=new glm::mat4[6*max_pl_shadow];

	SFBO=new FrameBuffer(glm::ivec2(4096,4096));
	PSFBO=new FrameBuffer(glm::ivec2(512,512));
	//PSFBO2=new FrameBuffer(glm::ivec2(512,512));

    SFBO->push_depth_texture(Texture2DArr::gen_texture2DArr(glm::ivec3(SFBO->size.x,SFBO->size.y,max_l_shadow),
    		GL_DEPTH_COMPONENT32F,GL_DEPTH_COMPONENT,GL_FLOAT,P_Linear));
    PSFBO->push_depth_texture(Texture2DArr::gen_texture2DArr(glm::ivec3(PSFBO->size.x,PSFBO->size.y,6*max_pl_shadow),
    		GL_DEPTH_COMPONENT32F,GL_DEPTH_COMPONENT,GL_FLOAT,P_Linear));

    /*for(unsigned i=0;i<max_pl_shadow;i++){
    	PSFBO2->push_depth_texture(TextureCubeMap::gen_CubeMap(glm::ivec2(PSFBO2->size.x,PSFBO2->size.y),
    	    		GL_DEPTH_COMPONENT32F,GL_DEPTH_COMPONENT,GL_FLOAT,P_Linear));
    }*/
	shaderMultiShadowMapping=new Shader();
	shaderMultiShadowMapping->LoadShader("files/shader/shadow/multiShadowMapping/MultiShadowMapping.vert",
			"files/shader/shadow/multiShadowMapping/MultiShadowMapping.geo",
			"files/shader/shadow/multiShadowMapping/MultiShadowMapping.frag");
	shaderCubeShadowMapping=new Shader();
	shaderCubeShadowMapping->LoadShader("files/shader/shadow/cubeShadowMapping/CubeShadowMapping.vert",
			"files/shader/shadow/cubeShadowMapping/CubeShadowMapping.geo",
			"files/shader/shadow/cubeShadowMapping/CubeShadowMapping.frag");
}
ShadowData::~ShadowData() {
	delete[] LVP;
	delete[] PLVP;
	delete SFBO;
	delete PSFBO;

	delete shaderMultiShadowMapping;
	delete shaderCubeShadowMapping;
}
void ShadowData::sent_uniform(Shader *shader){
	Uniform::sentMat4Arr(shader->programID,LVP,s_num,std::string("parallelLVP[0]"));
	Uniform::sentMat4Arr(shader->programID,PLVP,6*ps_num,std::string("pointLVP[0]"));

	SFBO->depth_textures.at(0)->sent_uniform(shader,10,"depthMaps");
	//Texture::usetextureVec(shader,SFBO->depth_textures,3,"depthMap");
	//0~2 is preserve for texture and normal mapping
	PSFBO->depth_textures.at(0)->sent_uniform(shader,11,"pointdepthMaps");
	//Texture::usetextureVec(shader,PSFBO2->depth_textures,12,"cubedepthMap");

	//Texture::usetextureVec(shader,PSFBO->depth_textures,4,"pointdepthMap");
}
void ShadowData::gen_shadow_map(std::vector<PointLight*>&point_lights,
		std::vector<ParallelLight*>&lights,Camera *camera,
		double shadow_dis,Draw *d_obj){
	gen_parallelLights_LVP(lights,camera,shadow_dis);
	gen_shadows(shaderMultiShadowMapping,SFBO,LVP,s_num,d_obj);//shaderMultiShadowMapping

	gen_pointLight_LVP(point_lights);
	//for(int i=0;i<ps_num;i++){
		//gen_shadows(shaderCubeShadowMapping,PSFBO2,&PLVP[6*i],6,d_obj,i);//shaderMultiShadowMapping
		//gen_shadows(shaderCubeShadowMapping,PSFBO,&PLVP[6*i],6,d_obj,0,6*i);//shaderMultiShadowMapping
	//}

	gen_shadows(shaderCubeShadowMapping,PSFBO,PLVP,6*ps_num,d_obj);//shaderMultiShadowMapping
}
void ShadowData::gen_parallelLights_LVP(std::vector<ParallelLight*>&para_lights,Camera *camera,double shadow_dis){
	double shadow_size=(shadow_dis/sqrt(camera->look_dis()+1.0));
	s_num=0;
	for(unsigned i=0;i<para_lights.size();i++){
		if(para_lights.at(i)->shadow&&s_num<(int)max_l_shadow){
			LVP[s_num++]=para_lights.at(i)->get_LVP(SFBO->aspect(),shadow_size,camera->look_at);
		}
	}
}
void ShadowData::gen_shadows(Shader* shader,FrameBuffer* FBO,glm::mat4 *LVP,int s_num,Draw *d_obj,
		int depth_tex,int start_layer){
	shader->active_shader();

	FBO->bind_depth_texture(depth_tex);
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);//clear buffer
	shader->sent_Uniform("LVP_num",s_num);
	shader->sent_Uniform("start_layer",start_layer);
	Uniform::sentMat4Arr(shader->programID,LVP,s_num,std::string("LVP"));
	d_obj->draw_shadow(shader);
}
void ShadowData::gen_pointLight_LVP(std::vector<PointLight*>&point_lights){
	ps_num=0;
	for(unsigned i=0;i<point_lights.size();i++){
		if(point_lights.at(i)->shadow&&ps_num<(int)max_pl_shadow){
			for(int n=0;n<6;n++){
				PLVP[6*ps_num+n]=point_lights.at(i)->get_LVP(PSFBO->aspect(),n);
			}
			ps_num++;
		}
	}
}

