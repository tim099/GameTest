#include "class/input/mouse/Mouse.h"
#include "class/display/buffer/frameBuffer/FrameBuffer.h"
#include <iostream>
Mouse::Mouse() {
	prev_pos=glm::ivec2(-1,-1);
	scroll=0;
	left=0,right=0,mid=0;
}
Mouse::~Mouse() {

}
glm::vec2 Mouse::get_screen_space_pos(glm::ivec2 screen_size){
	glm::vec2 p;
	p.x=(((double)2*(pos.x)/(double)screen_size.x)-1.0f);
	p.y=(((double)2*(screen_size.y-pos.y)/(double)screen_size.y)-1.0f);
	return p;
}
glm::vec3 Mouse::get_world_space_pos(FrameBuffer* FBO,glm::ivec2 screen_size,glm::mat4 inverseMat){
	glm::vec4 mwpos=FBO->get_world_space_pos(get_screen_space_pos(screen_size),inverseMat);
	world_pos=glm::vec3(mwpos.x,mwpos.y,mwpos.z);
	return glm::vec3(mwpos.x,mwpos.y,mwpos.z);
}
glm::ivec2 Mouse::pos_delta()const{
	if(prev_pos==glm::ivec2(-1,-1))return glm::ivec2(0,0);
	else return pos-prev_pos;
}
void Mouse::cursor_pos_callback(GLFWwindow* window,double x,double y){
	prev_pos=pos;
	pos.x=x;
	pos.y=y;
	//std::cout<<"mouse pos"<<pos.x<<","<<pos.y<<std::endl;
}
void Mouse::scroll_callback(GLFWwindow* window,double xoffset,double yoffset){
	//std::cout<<"scroll"<<xoffset<<","<<yoffset<<std::endl;
	scroll=yoffset;
}
void Mouse::mouse_button_callback(GLFWwindow* window,int button,int action,int mods){
		switch(button){
			case 0:
				if(action==1)left=true;
				else if(action==0)left=false;
				break;
			case 1:
				if(action==1)right=true;
				else if(action==0)right=false;
				break;
			case 2:
				if(action==1)mid=true;
				else if(action==0)mid=false;
				break;
			default:
				std::cout<<"unknow mouse but input"<<button<<std::endl;
		}

	//std::cout<<"button="<<button<<",action="<<action<<",mods="<<mods<<std::endl;
}
void Mouse::tic(){
	prev_pos=pos;
	scroll=0;
	//std::cout<<"mouse pos"<<pos.x<<","<<pos.y<<std::endl;
}
