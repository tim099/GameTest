#ifndef TASKCREATEMAPMODEL_H_
#define TASKCREATEMAPMODEL_H_
#include "class/tim/Thread/task/Task.h"
class DisplayMap;
class Model;
class TaskCreateMapModel : public Tim::Task{
public:
	TaskCreateMapModel(DisplayMap* dmap,int px,int pz);
	virtual ~TaskCreateMapModel();
	Model* mapmodel;
	int px;
	int pz;
protected:
	virtual void ExecuteTask();
	DisplayMap* dmap;
};

#endif /* TASKCREATEMAPMODEL_H_ */
