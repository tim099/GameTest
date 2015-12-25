#include "class/display/window/Window.h"
#include "class/tim/math/Math.h"
#include <GL/glew.h>
#include <GL/glfw3.h>
#include <iostream>

bool Window::glewinitial=false;
bool Window::glfwinitial=false;

Window::Window(glm::ivec2 _size,const char* name,bool full_screen) {
	creat_window(_size,name,full_screen);
	size=_size;
}
Window::~Window() {

}
void Window::close_window(){
	glfwSetWindowShouldClose(get_window(),1);
}
void Window::swap_buffer()const{
	glfwSwapBuffers(get_window());
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
float Window::aspect()const{
	return Tim::Math::aspect(size);
}
glm::ivec2 Window::get_size()const{
	return size;
}
void Window::render_on(){
	wglMakeCurrent(dc,lrc);
}
void Window::render_off(){
	wglMakeCurrent(0,0);
}
void Window::creat_window(glm::i16vec2 size,const char* name,bool full_screen){
	glfwinit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,1);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT,GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);
    if(full_screen)window=glfwCreateWindow(size.x,size.y,name,glfwGetPrimaryMonitor(),NULL);//full screen
    else window=glfwCreateWindow(size.x,size.y,name,NULL,NULL);
    glfwMakeContextCurrent(window);
    dc=wglGetCurrentDC();
    lrc=wglGetCurrentContext();
    glfwSetInputMode(window,GLFW_STICKY_KEYS,GL_TRUE);
    glewinit();
}
GLFWwindow* Window::get_window()const{
	return window;
}
