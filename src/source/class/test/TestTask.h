#ifndef TESTTASK_H_
#define TESTTASK_H_
#include "class/tim/Thread/task/Task.h"
class TestTask : public Tim::Task{
public:
	TestTask();
	virtual ~TestTask();
protected:
	virtual void ExecuteTask();
};

#endif /* TESTTASK_H_ */
