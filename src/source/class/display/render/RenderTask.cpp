#include "class/display/render/RenderTask.h"
#include "class/display/window/Window.h"
#include <iostream>
namespace Display{
RenderTask::RenderTask(Renderer *_renderrer) {
	renderrer=_renderrer;
}
RenderTask::~RenderTask() {

}
void RenderTask::ExecuteTask(){
	//std::cout<<"render start"<<std::endl;
	Window::get_cur_object()->render_on();
	renderrer->render();
	Window::get_cur_object()->render_off();
	//std::cout<<"render end"<<std::endl;
}
}
