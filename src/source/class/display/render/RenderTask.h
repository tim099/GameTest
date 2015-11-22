#ifndef RENDERTASK_H_
#define RENDERTASK_H_
#include "class/tim/Thread/Thread.h"
#include "class/display/render/Renderer.h"
class Window;
class RenderTask : public Tim::Task{
public:
	RenderTask(Renderer *renderrer,Window *window);
	virtual ~RenderTask();
protected:
	virtual void ExecuteTask();
	Renderer *renderrer;
	Window *window;
};

#endif /* RENDERTASK_H_ */
