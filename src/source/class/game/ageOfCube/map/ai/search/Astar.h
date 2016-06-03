#ifndef SOURCE_CLASS_GAME_AGEOFCUBE_MAP_AI_ASTAR_H_
#define SOURCE_CLASS_GAME_AGEOFCUBE_MAP_AI_ASTAR_H_
#include "class/game/ageOfCube/map/ai/search/Finder.h"
#include "class/game/ageOfCube/map/ai/search/SearchTask.h"
#include <queue>
namespace AOC {
namespace AI {
namespace search{
class Astar {
public:
	Astar();
	virtual ~Astar();
	void search(SearchTask* task);
	std::queue<SearchTask*> tasks;
};
}
}
} /* namespace AI */

#endif /* SOURCE_CLASS_GAME_AGEOFCUBE_MAP_AI_ASTAR_H_ */
