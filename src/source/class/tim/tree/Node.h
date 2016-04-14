#ifndef SOURCE_CLASS_TIM_TREE_NODE_H_
#define SOURCE_CLASS_TIM_TREE_NODE_H_
#include <vector>
namespace Tim {
template<class Key,class Data>
class Node {
public:
	Node();
	virtual ~Node();

	void insert(Node<Key,Data>* child);
	void remove(Key k);
	Node<Key,Data>* find(Key k);


	Node<Key,Data>* parent;
	std::vector<Node<Key,Data>*>children;
	Key key;
	Data data;
};

} /* namespace Tim */
#include "class/tim/tree/Node.cpp"
#endif /* SOURCE_CLASS_TIM_TREE_NODE_H_ */
