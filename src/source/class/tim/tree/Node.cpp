#ifndef SOURCE_CLASS_TIM_TREE_NODE_CPP_
#define SOURCE_CLASS_TIM_TREE_NODE_CPP_
#include "class/tim/tree/Node.h"
#include <iostream>
namespace Tim {
template<class Key,class Data>
Node<Key,Data>::Node() {
	parent=0;
}
template<class Key,class Data>
Node<Key,Data>::~Node() {
	for(unsigned i=0;i<children.size();i++){
		delete children.at(i);
	}
}
template<class Key,class Data>
void Node<Key,Data>::insert(Node<Key,Data>* child){
	child->parent=this;
	children.push_back(child);
}
template<class Key,class Data>
void Node<Key,Data>::remove(Key k){
	Node<Key,Data>* child=0;
	for(unsigned i=0;i<children.size();i++){
		if(k==children.at(i)->Key){
			child=children.at(i);
			children.at(i)=children.back();
			children.pop_back();
			break;
		}
	}
	if(child){
		delete child;
	}else{
		std::cerr<<"void Node<Key,Data>::remove fail,node not find"<<std::endl;
	}
}
template<class Key,class Data>
Node<Key,Data>* Node<Key,Data>::find(Key k){
	for(unsigned i=0;i<children.size();i++){
		if(k==children.at(i)->key){
			return children.at(i);
		}
	}
	return 0;
}
} /* namespace Tim */

#endif /* SOURCE_CLASS_TIM_TREE_NODE_CPP_ */
