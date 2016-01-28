#include "class/display/render/RenderTask.h"
#include "class/display/window/Window.h"
#include <iostream>
RenderTask::RenderTask(Renderer *_renderrer) {
	renderrer=_renderrer;
}
RenderTask::~RenderTask() {

}
void RenderTask::ExecuteTask(){
	//std::cout<<"render start"<<std::endl;
	renderrer->render();
	//std::cout<<"render end"<<std::endl;
}
