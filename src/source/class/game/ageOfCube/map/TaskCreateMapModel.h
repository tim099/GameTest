#ifndef TASKCREATEMAPMODEL_H_
#define TASKCREATEMAPMODEL_H_
#include "class/tim/Thread/task/Task.h"
namespace AOC{
class DisplayMap;
}

class Model;
class TaskCreateMapModel : public Tim::Task{
public:
	TaskCreateMapModel(AOC::DisplayMap* dmap,int px,int pz);
	virtual ~TaskCreateMapModel();
	int px;
	int pz;
protected:
	virtual void ExecuteTask();
	AOC::DisplayMap* dmap;
};

#endif /* TASKCREATEMAPMODEL_H_ */
