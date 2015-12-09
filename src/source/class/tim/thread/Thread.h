#ifndef THREAD_H_
#define THREAD_H_
#include <windows.h>
#include <queue>
#include "class/tim/thread/task/Task.h"
#include "class/tim/thread/ExecuteDone.h"
#include "class/tim/thread/mutex/Mutex.h"



//warning!!do not delete Thread directly,please use Terminate() to delete Thread

//#include <process.h>

//IDLE_PRIORITY_CLASS
//BELOW_NORMAL_PRIORITY_CLASS
//NORMAL_PRIORITY_CLASS
//ABOVE_NORMAL_PRIORITY_CLASS
//HIGH_PRIORITY_CLASS
//REALTIME_PRIORITY_CLASS
namespace Tim {

class Thread{
public:
	Thread(int priority=THREAD_PRIORITY_NORMAL,Tim::ExecuteDone *done=0);
	virtual ~Thread();
	/*
	 *start execute task inside this thread
	 *and automatically call wait() when finished
	 */
	void start();
	/*
	 *stop the thread until you call start() again
	 */
	void sleep();
	/*
	 * set priority of this thread
	 */
	void set_priority(int priority);
	/*
	 * push a task into thread queue
	 */
	void push_task(Task* task);
	/*
	 *wait for this thread until all task done
	 */
	void wait_for_this(DWORD time=INFINITE);
	/*
	 *this function only call by the win32 api CreateThread()
	 *execute task in this function
	 */
	virtual void ExecuteTask();
	/*
	 * return true if thread is suspended
	 */
	bool Suspended()const;
	/*
	 *return true if this thread is going to be terminate
	 */
	bool END()const;
	/*
	 * return true if all task are done
	 */
	bool DONE()const;
	/*
	 * call to terminate this thread,and it will automatically delete this thread
	 * use this instead of delete thread directly!!
	 */
	void Terminate();
protected:
	static DWORD WINAPI Execute(LPVOID lpParameter);

	std::queue<Task*> task_q;
	bool end;
	bool terminate;
	bool thread_start;
	Mutex *threadMutex;
	ExecuteDone *done;
	HANDLE threadhandle;
	DWORD ThreadID;
};

} /* namespace Tim */

#endif /* THREAD_H_ */
