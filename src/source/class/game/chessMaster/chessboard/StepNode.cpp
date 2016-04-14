#include "class/game/chessMaster/chessboard/StepNode.h"

namespace CM {

StepNode::StepNode() {

}
StepNode::StepNode(Step _key,StepData _data){
	key=_key;data=_data;
}
StepNode::~StepNode() {

}
void StepNode::save(FILE * file){
	key.save(file);
	data.save(file);
	fprintf(file,"\n");
	save_children(file);
}
void StepNode::load(FILE * file){
	key.load(file);
	data.load(file);
	load_children(file);

}
void StepNode::save_children(FILE * file){
	fprintf(file,"%u\n",children.size());
	StepNode* child;
	for(unsigned i=0;i<children.size();i++){
		child=(StepNode*)children.at(i);
		child->save(file);
	}
}
void StepNode::load_children(FILE * file){
	unsigned children_size;
	fscanf(file,"%u\n",&children_size);
	StepNode* child;
	for(unsigned i=0;i<children_size;i++){
		child=new StepNode();
		child->load(file);
		insert(child);
	}
}
} /* namespace CM */
