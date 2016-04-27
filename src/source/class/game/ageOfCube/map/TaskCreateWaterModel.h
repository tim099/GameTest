#ifndef SOURCE_CLASS_GAME_MAP_TASKCREATEWATERMODEL_H_
#define SOURCE_CLASS_GAME_MAP_TASKCREATEWATERMODEL_H_

#include "class/tim/Thread/task/Task.h"
class Model;
namespace AOC{
class DisplayMap;
class TaskCreateWaterModel: public Tim::Task {
public:
	TaskCreateWaterModel(DisplayMap* dmap,int px,int pz);
	virtual ~TaskCreateWaterModel();
	int px;
	int pz;
protected:
	virtual void ExecuteTask();
	DisplayMap* dmap;
};
}
#endif /* SOURCE_CLASS_GAME_MAP_TASKCREATEWATERMODEL_H_ */
