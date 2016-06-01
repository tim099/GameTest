#include "class/game/ageOfCube/map/ai/search/Node.h"

namespace AOC {
namespace AI {
namespace search {

Node::Node(Node* _parent) {
	parent=_parent;
}
Node::~Node() {

}

} /* namespace search */
} /* namespace AI */
} /* namespace AOC */
