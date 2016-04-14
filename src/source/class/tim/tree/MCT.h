#ifndef SOURCE_CLASS_TIM_TREE_MCT_H_
#define SOURCE_CLASS_TIM_TREE_MCT_H_
#include "class/tim/tree/Node.h"
namespace Tim {
template<class key,class data>
class MCT {
public:
	MCT();
	virtual ~MCT();


	Node<key,data>* root;
};

} /* namespace Tim */
#include "class/tim/tree/MCT.cpp"
#endif /* SOURCE_CLASS_TIM_TREE_MCT_H_ */
