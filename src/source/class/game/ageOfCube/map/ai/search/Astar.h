#ifndef SOURCE_CLASS_GAME_AGEOFCUBE_MAP_AI_ASTAR_H_
#define SOURCE_CLASS_GAME_AGEOFCUBE_MAP_AI_ASTAR_H_
#include "class/game/ageOfCube/map/ai/search/Finder.h"
#include "class/game/ageOfCube/map/ai/search/SearchTask.h"
#include "class/tim/thread/ThreadPool.h"
#include "class/tim/globalObject/GlobalObject.h"
#include "class/tim/array/Array3D.h"
#include "class/tim/objectpool/ObjPool.h"
namespace AOC {
namespace AI {
namespace search{
class Astar : public Tim::GlobalObject<Astar>{
public:
	Astar();
	virtual ~Astar();
	void push_task(SearchTask* task){//parallel search
		task->init(this);
		thread_pool->push_task(task);
	}
	void search(Tim::SmartPointer<Finder>& finder);
private:
	//Tim::Array3D<bool> *visited;
	Tim::ObjPool<Node> *node_pool;
	Tim::ThreadPool *thread_pool;
};
}
}
} /* namespace AI */

#endif /* SOURCE_CLASS_GAME_AGEOFCUBE_MAP_AI_ASTAR_H_ */
