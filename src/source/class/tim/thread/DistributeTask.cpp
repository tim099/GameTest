#include "class/tim/thread/DistributeTask.h"
#include "class/tim/thread/ThreadPool.h"
namespace Tim {

DistributeTask::DistributeTask(ThreadPool *_thread_pool) {
	thread_pool=_thread_pool;
}
DistributeTask::~DistributeTask() {

}
void DistributeTask::done(Tim::Thread* thread){
	thread_pool->distribute_task(thread);
}
} /* namespace Tim */
