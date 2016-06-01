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
	Node* parent;
	math::vec3<int> pos;
};

} /* namespace search */
} /* namespace AI */
} /* namespace AOC */

#endif /* SOURCE_CLASS_GAME_AGEOFCUBE_MAP_AI_SEARCH_NODE_H_ */
