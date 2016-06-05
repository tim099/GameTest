#ifndef SOURCE_CLASS_GAME_AGEOFCUBE_MAP_AI_SEARCH_SEARCHTASK_H_
#define SOURCE_CLASS_GAME_AGEOFCUBE_MAP_AI_SEARCH_SEARCHTASK_H_
#include "class/game/ageOfCube/map/ai/search/Finder.h"
#include "class/tim/pointer/SmartPointer.h"
#include "class/tim/Thread/task/Task.h"
namespace AOC {
namespace AI {
namespace search {
class Astar;
class SearchTask : public Tim::Task{
public:
	SearchTask(Tim::SmartPointer<Finder> finder);
	virtual ~SearchTask();
	void init(Astar* _astar){
		astar=_astar;
	}
protected:
	virtual void ExecuteTask();
	Astar* astar;
	Tim::SmartPointer<Finder> finder;
};

} /* namespace search */
} /* namespace AI */
} /* namespace AOC */

#endif /* SOURCE_CLASS_GAME_AGEOFCUBE_MAP_AI_SEARCH_SEARCHTASK_H_ */
