#ifndef SOURCE_CLASS_GAME_SCENEINITTASK_H_
#define SOURCE_CLASS_GAME_SCENEINITTASK_H_

#include "class/tim/thread/task/Task.h"

class SceneInitTask: public Tim::Task {
public:
	SceneInitTask();
	virtual ~SceneInitTask();
};

#endif /* SOURCE_CLASS_GAME_SCENEINITTASK_H_ */
