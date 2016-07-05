#include "class/display/light/LightControl.h"
#include "class/display/texture/texture2D/Texture2D.h"
#include "class/display/shader/Shader.h"
#include "class/display/camera/Camera.h"
#include "class/tim/math/Math.h"
#include "class/display/buffer/frameBuffer/FrameBuffer.h"
#include "class/display/uniform/Uniform.h"
#include "class/display/draw/Draw.h"
#include "class/game/Config.h"
#include <cstdio>
namespace Display{
LightControl::LightControl(float _draw_dis) {
	game::Config* config=game::Config::get_cur_object();

	draw_dis=_draw_dis;
	if(config){
		//std::cout<<"LightControl::LightControl config!!"<<std::endl;
		shadowData=new ShadowData(3,4,config->shadow_quality);
		shadowData->enable_PSSM=config->enable_pssm;
	}else{
		shadowData=new ShadowData(3,4);
	}

	shadow_dis=1.0;
}
LightControl::~LightControl() {
	Display::Draw* draw=Display::Draw::get_cur_object();
	if(draw->lightControl==this){
		draw->set_lightControl(0);
	}
	clear_temp_data();
	for(unsigned i=0;i<point_lights.size();i++){
		delete point_lights.at(i);
	}
	for(unsigned i=0;i<parallel_lights.size();i++){
		delete parallel_lights.at(i);
	}
	for(unsigned i=0;i<cube_lights.size();i++){
		delete cube_lights.at(i);
	}
	delete shadowData;
}
void LightControl::gen_shadow(Shader *shaderShadowMapping,Camera *camera,Draw *d_obj){
	choose_point_light(camera->pos);
	shadowData->gen_shadow_map(shaderShadowMapping,
			selected_point_lights,parallel_lights,camera,shadow_dis,d_obj);
}
PointLight* LightControl::get_point_light(int i)const{
	return point_lights.at(i);
}
ParallelLight* LightControl::get_parallel_light(int i)const{
	return parallel_lights.at(i);
}
unsigned LightControl::parallel_light_size()const{
	return parallel_lights.size();
}
unsigned LightControl::point_light_size()const{
	return point_lights.size();
}
void LightControl::remove_light(Display::PointLight* l){
	for(unsigned i=0;i<point_lights.size();i++){
		if(point_lights.at(i)==l){
			delete l;
			point_lights.at(i)=point_lights.back();
			point_lights.pop_back();
		}
	}
}
void LightControl::remove_light(Display::ParallelLight* l){
	for(unsigned i=0;i<parallel_lights.size();i++){
		if(parallel_lights.at(i)==l){
			delete l;
			parallel_lights.at(i)=parallel_lights.back();
			parallel_lights.pop_back();
		}
	}
}
void LightControl::remove_light(Display::CubeLight* l){
	for(unsigned i=0;i<cube_lights.size();i++){
		if(cube_lights.at(i)==l){
			delete l;
			cube_lights.at(i)=cube_lights.back();
			cube_lights.pop_back();
		}
	}
}
void LightControl::push_light(Display::PointLight* l){
	point_lights.push_back(l);//lights.size()<MAX_LIGHT
}
void LightControl::push_light(Display::ParallelLight* l){
	parallel_lights.push_back(l);
}
void LightControl::push_light(Display::CubeLight* l){
	cube_lights.push_back(l);
}
void LightControl::push_temp_light(Display::CubeLight* l){
	temp_cube_lights.push_back(l);
}
void LightControl::push_temp_light(Display::PointLight* l){
	temp_point_lights.push_back(l);
}
void LightControl::push_temp_light(Display::ParallelLight* l){
	temp_parallel_lights.push_back(l);
}
void LightControl::choose_point_light(glm::vec3 camera_pos){
    selected_point_lights.clear();
    for(unsigned i=0;i<temp_point_lights.size();i++){
    	selected_point_lights.push_back(temp_point_lights.at(i));
    }
    for(unsigned i=0;i<point_lights.size();i++){
    	if(glm::length(camera_pos-point_lights.at(i)->pos)<draw_dis&&selected_point_lights.size()<MAX_POINT_LIGHT){
    		selected_point_lights.push_back(point_lights.at(i));
    	}
    }
}
void LightControl::clear_temp_data(){
    for(unsigned i=0;i<temp_parallel_lights.size();i++){
    	delete temp_parallel_lights.at(i);
    }
    temp_parallel_lights.clear();
    for(unsigned i=0;i<temp_point_lights.size();i++){
    	delete temp_point_lights.at(i);
    }
    temp_point_lights.clear();

    for(unsigned i=0;i<temp_cube_lights.size();i++){
    	//std::cout<<"test temp cube light"<<std::endl;
    	delete temp_cube_lights.at(i);

    }
    temp_cube_lights.clear();
}
void LightControl::sent_uniform(Shader *shader,glm::vec3 camera_pos){
	//try to sort by dis and merge far light!!

	shadowData->sent_uniform(shader);


    std::vector<glm::vec3>parallellight_vec;
    std::vector<glm::vec3>parallellight_color;
    std::vector<GLint>parallellight_shadow;


    unsigned parallellight_shadow_num=0;
    for(unsigned i=0;i<parallel_lights.size();i++){
    	parallellight_vec.push_back(parallel_lights.at(i)->vec);
    	parallellight_color.push_back(parallel_lights.at(i)->color);
    	if(parallel_lights.at(i)->shadow&&shadowData->max_l_shadow>parallellight_shadow_num){
    		parallellight_shadow.push_back(++parallellight_shadow_num);
    	}else{
    		parallellight_shadow.push_back(0);
    	}

    }

    choose_point_light(camera_pos);

    std::vector<glm::vec3>pointlight_pos;
    std::vector<glm::vec3>pointlight_color;
    std::vector<GLint>pointlight_shadow;
    PointLight *p_light;
    unsigned pointlight_shadow_num=0;

    for(unsigned i=0;i<selected_point_lights.size();i++){
    	p_light=selected_point_lights.at(i);
		pointlight_pos.push_back(p_light->pos);
		pointlight_color.push_back(p_light->color);
		if(p_light->shadow&&shadowData->max_pl_shadow>pointlight_shadow_num){
			pointlight_shadow.push_back(++pointlight_shadow_num);
		}else{
			pointlight_shadow.push_back(0);
		}
    }

    CubeLight *c_light;
    std::vector<glm::vec3>cubelight_pos;
    std::vector<glm::vec3>cubelight_color;
    std::vector<glm::vec3>cubelight_size;

    for(unsigned i=0;i<cube_lights.size();i++){
    	c_light=cube_lights.at(i);
    	cubelight_pos.push_back(c_light->pos);
    	cubelight_color.push_back(c_light->color);
    	if(c_light->size>0.0){
    		cubelight_size.push_back(glm::vec3(c_light->size,c_light->size,c_light->size));
    	}else{
    		cubelight_size.push_back(c_light->cube_size);
    	}

    }
    for(unsigned i=0;i<temp_cube_lights.size();i++){
    	//std::cout<<"test temp cube light"<<std::endl;
    	c_light=temp_cube_lights.at(i);
    	cubelight_pos.push_back(c_light->pos);
    	cubelight_color.push_back(c_light->color);
    	if(c_light->size>0.0){
    		cubelight_size.push_back(glm::vec3(c_light->size,c_light->size,c_light->size));
    	}else{
    		cubelight_size.push_back(c_light->cube_size);
    	}
    }
    glUniform1i(glGetUniformLocation(shader->programID,"parallellight_num"),
    		parallellight_vec.size());
    glUniform3fv(glGetUniformLocation(shader->programID,"parallellight_vec"),
    		parallellight_vec.size(),(const GLfloat*)(parallellight_vec.data()));
    glUniform3fv(glGetUniformLocation(shader->programID,"parallellight_color"),
    		parallellight_color.size(),(const GLfloat*)(parallellight_color.data()));
    glUniform1iv(glGetUniformLocation(shader->programID,"parallellight_shadow"),
    		parallellight_shadow.size(),(const GLint*)(parallellight_shadow.data()));


    glUniform1i(glGetUniformLocation(shader->programID,"pointlight_num"),pointlight_pos.size());
    glUniform3fv(glGetUniformLocation(shader->programID,"pointlight_pos"),
    		pointlight_pos.size(),(const GLfloat*)(pointlight_pos.data()));
    glUniform3fv(glGetUniformLocation(shader->programID,"pointlight_color"),
    		pointlight_color.size(),(const GLfloat*)(pointlight_color.data()));
    glUniform1iv(glGetUniformLocation(shader->programID,"pointlight_shadow"),
    		pointlight_shadow.size(),(const GLint*)(pointlight_shadow.data()));

    glUniform1i(glGetUniformLocation(shader->programID,"cubelight_num"),cubelight_pos.size());
    glUniform3fv(glGetUniformLocation(shader->programID,"cubelight_pos"),
    		cubelight_pos.size(),(const GLfloat*)(cubelight_pos.data()));
    glUniform3fv(glGetUniformLocation(shader->programID,"cubelight_color"),
    		cubelight_color.size(),(const GLfloat*)(cubelight_color.data()));
    glUniform3fv(glGetUniformLocation(shader->programID,"cubelight_size"),
    		cubelight_size.size(),(const GLfloat*)(cubelight_size.data()));
}
}
