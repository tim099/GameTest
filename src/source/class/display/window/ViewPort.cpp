#include "class/display/window/ViewPort.h"
#include "class/tim/math/Math.h"
#include <GL/glew.h>
#include <GL/glfw3.h>
#include <iostream>
ViewPort::ViewPort() {

}
ViewPort::~ViewPort() {

}
float ViewPort::get_cur_viewport_aspect(){
	return Tim::Math::aspect(get_cur_viewport_size());
}
glm::ivec2 ViewPort::get_cur_viewport_size(){
	GLint viewport[4];
	glGetIntegerv( GL_VIEWPORT, viewport );
	return glm::ivec2(viewport[2]-viewport[0],viewport[3]-viewport[1]);
}
