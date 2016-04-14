#include "class/game/chessMaster/chessboard/BoardMCT.h"
#include "class/tim/file/File.h"
namespace CM {

BoardMCT::BoardMCT() {
	step_root=new StepNode();
	root=step_root;
}
BoardMCT::~BoardMCT() {
	delete step_root;
}
void BoardMCT::save(std::string path){
	FILE * file = fopen(path.c_str(),"w+t");
	step_root->save(file);
	fclose(file);
}
void BoardMCT::load(std::string path){
	if(!Tim::File::check_if_file_exist(path)){
		std::cerr<<"no MCT find create new:"<<path<<std::endl;
		save(path);
	}
	delete step_root;
	step_root=new StepNode();
	FILE * file = fopen(path.c_str(),"r");
	step_root->load(file);
	fclose(file);
}
StepNode* BoardMCT::find(StepNode *cur,Step step){
	StepNode* next=(StepNode*)cur->find(step);
	return next;
}
StepNode* BoardMCT::find_and_expand(StepNode *cur,Step step){
	StepNode* next=(StepNode*)cur->find(step);
	if(!next){
		next=new StepNode(step,StepData());
		cur->insert(next);
	}
	return next;
}
} /* namespace CM */
