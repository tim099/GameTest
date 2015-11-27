#ifndef TASK_H_
#define TASK_H_
#include "class/tim/thread/mutex/Mutex.h"
namespace Tim {

class Task {
friend class Thread;
public:
	Task();
	virtual ~Task();
	void Execute();
	bool Done()const;
	bool AutoTerminate()const;
protected:
	virtual void TaskDone();
	virtual void ExecuteTask()=0;
	bool done;
	bool auto_terminate;
};

} /* namespace Tim */

#endif /* TASK_H_ */
