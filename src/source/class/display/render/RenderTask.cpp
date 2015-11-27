#include "class/display/render/RenderTask.h"
#include "class/display/window/Window.h"
#include <iostream>
RenderTask::RenderTask(Renderer *_renderrer,Window *_window) {
	renderrer=_renderrer;
	window=_window;
}
RenderTask::~RenderTask() {

}
void RenderTask::ExecuteTask(){
	//std::cout<<"render start"<<std::endl;
	renderrer->render();
	//std::cout<<"render end"<<std::endl;
}
