#ifndef RENDERTASK_H_
#define RENDERTASK_H_
#include "class/tim/Thread/Thread.h"
#include "class/display/render/Renderer.h"
class Window;
namespace Display{
class RenderTask : public Tim::Task{
public:
	RenderTask(Renderer *renderrer);
	virtual ~RenderTask();
protected:
	virtual void ExecuteTask();
	Renderer *renderrer;

};
}
#endif /* RENDERTASK_H_ */
