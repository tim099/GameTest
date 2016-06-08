#ifndef SOURCE_CLASS_GAME_AGEOFCUBE_MAP_AI_FINDER_H_
#define SOURCE_CLASS_GAME_AGEOFCUBE_MAP_AI_FINDER_H_
#include "class/game/ageOfCube/map/ai/search/Node.h"
#include "class/tim/math/vec3.h"
#include <cstdio>
namespace AOC {
namespace AI {
namespace search{
class Finder {
public:
	Finder();
	virtual ~Finder();
	virtual bool check_find(Node* node)=0;
	virtual void node_find(Node* node)=0;
	virtual double node_score(Node* node){return 0;}
	virtual	math::vec3<int> get_start_pos()=0;
	virtual	int get_size()=0;
	virtual	double get_double_size();

	void save(FILE* file);
	void load(FILE* file);

	int min_search_times;//if find and reach min_search_times then stop
	int max_search_times;//if reach max_search_times then stop(no matter find or not
	int find;//find target
	int search_done;//search_done flag
	int stop_search;//stop this search request
protected:
	virtual void save_finder(FILE* file){}
	virtual void load_finder(FILE* file){}
};
}
}
} /* namespace AI */

#endif /* SOURCE_CLASS_GAME_AGEOFCUBE_MAP_AI_FINDER_H_ */
