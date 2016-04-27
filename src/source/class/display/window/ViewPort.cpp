#include "class/display/window/ViewPort.h"
#include "class/tim/math/Math.h"

#include <iostream>
namespace Display{
GLint ViewPort::x=0;
GLint ViewPort::y=0;
GLsizei ViewPort::width=0;
GLsizei ViewPort::height=0;
glm::ivec2 ViewPort::window_size=glm::ivec2(0,0);
ViewPort::ViewPort() {

}
ViewPort::~ViewPort() {

}
float ViewPort::get_cur_window_aspect(){
	return Tim::Math::aspect(get_cur_window_size());
}
void ViewPort::set_window_size(glm::ivec2 size){
	window_size=size;
}
glm::ivec2 ViewPort::get_cur_window_size(){
	return window_size;
}
void ViewPort::set_viewport(GLint _x, GLint _y, GLsizei _width, GLsizei _height){
	x=_x;
	y=_y;
	width=_width;
	height=_height;
	glViewport(x,y,width,height);
}
float ViewPort::get_cur_viewport_aspect(){
	float aspect=Tim::Math::aspect(get_cur_viewport_size());
	//std::cout<<"cur aspect="<<aspect<<std::endl;
	return aspect;
}
glm::ivec2 ViewPort::get_cur_viewport_size(){
	//GLint viewport[4];
	//glGetIntegerv( GL_VIEWPORT, viewport );
	//return glm::ivec2(viewport[2]-viewport[0],viewport[3]-viewport[1]);
	return glm::ivec2(width-x,height-y);
}
}
