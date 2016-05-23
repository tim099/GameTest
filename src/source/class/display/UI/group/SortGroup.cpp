#include "class/display/UI/group/SortGroup.h"
#include "class/display/window/ViewPort.h"
namespace UI {

SortGroup::SortGroup() {

}
SortGroup::~SortGroup() {

}
void SortGroup::Parse_UIScript(std::istream &is,std::string &line){
	if (line == "Interval:") {
		math::vec2<float> _interval;
		is>>_interval.x;
		is>>_interval.y;
		set_interval(_interval);
	}
}
void SortGroup::Parse_UIScript(std::ostream &os){
	os<<"	"<<"Interval:"<<std::endl;
	os<<"		"<<interval.x<<" "<<interval.y<<std::endl;

}
void SortGroup::update(){
	sort();
}
void SortGroup::set_interval(math::vec2<float> _interval){
	interval=_interval;
	//interval.y*=ViewPort::get_cur_window_aspect();
}
void SortGroup::sort(){
	UIObject *child;
	math::vec2<float> del=interval;
	del.y*=Display::ViewPort::get_cur_window_aspect();
	float val;
	for(unsigned i=0;i<childs.size();i++){
		child=childs.at(i);
		val=i;
		child->set_relative_pos(val*del);
	}
}
} /* namespace UI */
