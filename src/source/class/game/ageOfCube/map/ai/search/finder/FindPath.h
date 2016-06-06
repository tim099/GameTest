#ifndef SOURCE_CLASS_GAME_AGEOFCUBE_MAP_AI_SEARCH_FINDER_FINDPATH_H_
#define SOURCE_CLASS_GAME_AGEOFCUBE_MAP_AI_SEARCH_FINDER_FINDPATH_H_
#include "class/game/ageOfCube/map/ai/search/Finder.h"
#include <vector>

namespace AOC {
namespace AI {
namespace search {

class FindPath : public Finder{
public:
	FindPath();
	FindPath(const math::vec3<double>&pos,const double &size,math::vec3<int>des,int dis=0);
	virtual ~FindPath();
	virtual void node_find(Node* node);
	virtual bool check_find(Node* node);
	virtual double node_score(Node* node);
	virtual	math::vec3<int> get_start_pos();
	virtual	int get_size();
	virtual	double get_double_size();


	std::vector<math::vec3<double> >path;
	unsigned cur_at;
protected:
	virtual void save_finder(FILE* file);
	virtual void load_finder(FILE* file);
	void convert_path(Node* node);
	math::vec3<double>pos;
	math::vec3<int>des;
	math::vec3<int>des_min,des_max;
	double size;
	int dis;
};

} /* namespace search */
} /* namespace AI */
} /* namespace AOC */

#endif /* SOURCE_CLASS_GAME_AGEOFCUBE_MAP_AI_SEARCH_FINDER_FINDPATH_H_ */
