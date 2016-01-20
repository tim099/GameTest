#include "class/input/mouse/Mouse.h"
#include "class/display/buffer/frameBuffer/FrameBuffer.h"
#include "class/tim/math/Math.h"
#include <iostream>

Mouse* Mouse::rigister_mouse=0;
Mouse::Mouse() {
	prev_pos=glm::ivec2(-1,-1);
	scroll=0;
	left=0,right=0,mid=0;
	left_click=false;
	right_click=false;
	mid_click=false;
}
Mouse::~Mouse() {

}
void Mouse::cursor_pos_callback(GLFWwindow* window, double x, double y){
	rigister_mouse->cursor_pos_input(window,x,y);
}
void Mouse::scroll_callback(GLFWwindow* window, double xoffset, double yoffset){
	rigister_mouse->scroll_input(window,xoffset,yoffset);
}
void Mouse::mouse_button_callback(GLFWwindow* window, int button, int action, int mods){
	rigister_mouse->mouse_button_input(window,button,action,mods);
}
void Mouse::callback_rigister(GLFWwindow *window){
	rigister_mouse=this;
	glfwSetCursorPosCallback(window,cursor_pos_callback);
	glfwSetScrollCallback(window,scroll_callback);
	glfwSetMouseButtonCallback(window,mouse_button_callback);
}
glm::vec2 Mouse::get_screen_space_pos(glm::ivec2 screen_size){
	screen_pos.x=(((double)2*(pos.x)/(double)screen_size.x)-1.0f);
	screen_pos.y=(((double)2*(screen_size.y-pos.y)/(double)screen_size.y)-1.0f);

	return screen_pos;
}
glm::vec2 Mouse::get_tex_space_pos(){
	return Tim::Math::convert_to_texcoord(screen_pos);
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
void Mouse::cursor_pos_input(GLFWwindow* window,double x,double y){
	prev_pos=pos;
	pos.x=x;
	pos.y=y;
	//std::cout<<"mouse pos"<<pos.x<<","<<pos.y<<std::endl;
}
void Mouse::scroll_input(GLFWwindow* window,double xoffset,double yoffset){
	//std::cout<<"scroll"<<xoffset<<","<<yoffset<<std::endl;
	scroll=yoffset;
}
void Mouse::mouse_button_input(GLFWwindow* window,int button,int action,int mods){
		left_click=false;
		right_click=false;
		mid_click=false;
		switch(button){
			case 0:
				if(action==1){
					left=true;
				}else if(action==0){
					if(left)left_click=true;
					left=false;
				}
				break;
			case 1:
				if(action==1){
					right=true;
				}else if(action==0){
					if(right)right_click=true;
					right=false;
				}
				break;
			case 2:
				if(action==1){
					mid=true;
				}else if(action==0){
					if(mid)mid_click=true;
					mid=false;
				}
				break;
			default:
				std::cout<<"unknow mouse but input"<<button<<std::endl;
		}

	//std::cout<<"button="<<button<<",action="<<action<<",mods="<<mods<<std::endl;
}
bool Mouse::get_left_click(){
	if(left_click){
		left_click=false;
		return true;
	}
	return false;
}
bool Mouse::get_right_click(){
	if(right_click){
		right_click=false;
		return true;
	}
	return false;
}
bool Mouse::get_mid_click(){
	if(mid_click){
		mid_click=false;
		return true;
	}
	return false;
}
void Mouse::tic(){
	prev_pos=pos;
	scroll=0;
	//std::cout<<"mouse pos"<<pos.x<<","<<pos.y<<std::endl;
}
