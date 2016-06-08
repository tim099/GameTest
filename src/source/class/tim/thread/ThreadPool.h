#ifndef THREADPOOL_H_
#define THREADPOOL_H_
#include "class/tim/thread/Thread.h"
#include "class/tim/thread/DistributeTask.h"
#include "class/tim/thread/mutex/Mutex.h"
#include <queue>
#include <vector>
namespace Tim {

class ThreadPool{
public:
	ThreadPool(int thread_num,int priority=NORMAL_PRIORITY_CLASS);
	virtual ~ThreadPool();


	void push_task(Task* task);
	void distribute_task(Tim::Thread* thread);
	void Terminate();
	bool ready_thread_terminate(Thread* thread);
	std::queue<Task*>task_q;
	std::queue<Thread*>ready_q;
	std::vector<Thread*>threads;
	Tim::Mutex Distribute_Mutex;
protected:

	DistributeTask *distributeTask;
};

} /* namespace Tim */

#endif /* THREADPOOL_H_ */
