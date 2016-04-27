#ifndef SOURCE_CLASS_GAME_MAP_TASKGENMAP_H_
#define SOURCE_CLASS_GAME_MAP_TASKGENMAP_H_
#include <glm/vec3.hpp>
#include "class/tim/thread/task/Task.h"
namespace AOC{
class Map;
class TaskGenMap: public Tim::Task {
public:
	TaskGenMap(AOC::Map* map,glm::ivec3 map_size,unsigned seed,int ground_height=150);
	virtual ~TaskGenMap();
protected:
	virtual void ExecuteTask();
	glm::ivec3 map_size;
	unsigned seed;
	int ground_height;
	AOC::Map* map;
};
}
#endif /* SOURCE_CLASS_GAME_MAP_TASKGENMAP_H_ */
