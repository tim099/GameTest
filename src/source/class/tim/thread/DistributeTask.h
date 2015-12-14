#ifndef DISTRIBUTETASK_H_
#define DISTRIBUTETASK_H_
#include "class/tim/thread/ExecuteDone.h"
namespace Tim {
class ThreadPool;
class DistributeTask : public Tim::ExecuteDone{
public:
	DistributeTask(ThreadPool *thread_pool);
	virtual ~DistributeTask();
	virtual void done(Tim::Thread* thread);
	void Terminate();
	ThreadPool *thread_pool;
protected:
	bool end;
};

} /* namespace Tim */

#endif /* DISTRIBUTETASK_H_ */
