#include "class/display/window/Window.h"
#include "class/display/window/ViewPort.h"
#include "class/tim/math/Math.h"
//#include <windows.h>
#include <GL/glew.h>
#include <GL/glfw3.h>
#include <iostream>
namespace Display{
bool Window::glewinitial=false;
bool Window::glfwinitial=false;

Window::Window(math::vec2<int> _size,std::string name,bool full_screen) {
	size=_size;
	creat_window(name,full_screen);
}
Window::~Window() {
	if(glfwinitial){
		glfwinitial=false;
		glfwTerminate();
	}
	if(glewinitial){
		//glewinitial=false;
	}

}
math::vec2<int> Window::get_screen_resolution(){
	math::vec2<int> res;
    const GLFWvidmode *mode = glfwGetVideoMode(glfwGetPrimaryMonitor());

    res.x= mode->width;
    res.y= mode->height;
    return res;
}
void Window::close_window(){
	glfwSetWindowShouldClose(get_window(),1);
}
void Window::swap_buffer()const{
	glfwSwapBuffers(get_window());
	glFlush();
}
int Window::WindowShouldClose()const{
	return glfwWindowShouldClose(get_window());
}
void Window::glewinit(){
	if(glewinitial)return;
	glewinitial=true;
    glewExperimental=true;
    glewInit();
}
void Window::glfwinit(){
	if(glfwinitial)return;
	glfwinitial=true;
	glfwInit();
}
float Window::get_aspect()const{
	return Tim::Math::aspect(size);
}
math::vec2<int> Window::get_size()const{
	return size;
}
void Window::set_veiwport(){
	ViewPort::set_window_size(size);
	ViewPort::set_viewport(0,0,size.x,size.y);
}
void Window::render_on(){
	//wglMakeCurrent(dc,lrc);
}
void Window::render_off(){
	//wglMakeCurrent(0,0);
}
void Window::creat_window(std::string name,bool full_screen){
	glfwinit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,1);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT,GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);
    if(full_screen){
    	window=glfwCreateWindow(size.x,size.y,name.c_str(),glfwGetPrimaryMonitor(),NULL);//full screen
    }else{
    	window=glfwCreateWindow(size.x,size.y,name.c_str(),NULL,NULL);
    }

    glfwMakeContextCurrent(window);
    //dc=wglGetCurrentDC();
    //lrc=wglGetCurrentContext();
    glfwSetInputMode(window,GLFW_STICKY_KEYS,GL_TRUE);
    glewinit();
    set_veiwport();
}
GLFWwindow* Window::get_window()const{
	return window;
}
}
