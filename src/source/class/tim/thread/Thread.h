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
	void start();
	void wait();
	void set_priority(int priority);
	void push_task(Task* task);
	void wait_for_this(DWORD time=INFINITE);
	virtual void ExecuteTask();
	bool END()const;
	bool DONE()const;
	void Terminate();
protected:
	static DWORD WINAPI Execute(LPVOID lpParameter);

	std::queue<Task*> task_q;
	bool end;
	bool terminate;
	ExecuteDone *done;
	HANDLE threadhandle;
	DWORD ThreadID;
};

} /* namespace Tim */

#endif /* THREAD_H_ */
