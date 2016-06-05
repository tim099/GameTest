#ifndef SOURCE_CLASS_GAME_AGEOFCUBE_MAP_AI_SEARCH_NODE_H_
#define SOURCE_CLASS_GAME_AGEOFCUBE_MAP_AI_SEARCH_NODE_H_
#include "class/tim/math/vec3.h"
namespace AOC {
namespace AI {
namespace search {

class Node {
public:
	Node(Node* parent=0);
	virtual ~Node();
	void init(Node* parent);
	Node* parent;
	math::vec3<int> pos;
	inline bool operator>(const Node& node)const{
		return (score>node.score);
	}
	inline bool operator<(const Node& node)const{
		return (score<node.score);
	}
	inline bool operator==(const Node& node){
		return (score==node.score);
	}
	bool jump;
	double score;
	double cur_dis;
};

struct NodeCmp{
	bool operator()(const Node* n1, const Node* n2) const{
		return (*n1)<(*n2) ;
	}
};
} /* namespace search */
} /* namespace AI */
} /* namespace AOC */

#endif /* SOURCE_CLASS_GAME_AGEOFCUBE_MAP_AI_SEARCH_NODE_H_ */
