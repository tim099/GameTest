#include "class/game/ageOfCube/map/ai/search/Node.h"

namespace AOC {
namespace AI {
namespace search {

Node::Node(Node* _parent) {
	init(_parent);
}
void Node::init(Node* _parent){
	parent=_parent;
	cur_dis=0.0;score=0.0;
	jump=false;
}
Node::~Node() {

}

} /* namespace search */
} /* namespace AI */
} /* namespace AOC */
