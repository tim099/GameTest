#include "class/tim/thread/DistributeTask.h"
#include "class/tim/thread/ThreadPool.h"
namespace Tim {

DistributeTask::DistributeTask(ThreadPool *_thread_pool) {
	thread_pool=_thread_pool;
	end=false;
}
DistributeTask::~DistributeTask() {

}
void DistributeTask::Terminate(){
	end=true;
}
void DistributeTask::done(Tim::Thread* thread){
	if(!end){
		thread_pool->distribute_task(thread);
	}else{
		if(thread_pool->ready_thread_terminate(thread)){
			delete thread_pool;
		}
	}
}
} /* namespace Tim */
