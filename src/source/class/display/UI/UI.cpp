#include "class/display/UI/UI.h"
#include "class/display/draw/Draw.h"
#include "class/display/UI/UIObjectCreator.h"
#include "class/tim/string/String.h"
//#include <iostream>
namespace UI {
UI* UI::cur_UI = 0;
UI::UI() {
	creator = new UIObjectCreator();
	cur_UI = this;
	set_name("UI");
}
UI::~UI() {
	delete creator;
}
void UI::Parse_Script(std::istream &is, std::string &line) {
	if (!strcmp(line.c_str(), "CreateUIObject:")) {
		Tim::String::get_line(is, line, true, true);
		UIObject* obj = creator->create(line);
		obj->Parse_UIObj_Script(is,line);
	}
}
void UI::Parse_Script(std::ostream &os){
	UIObject* obj;
	for(unsigned i=0;i<childs.size();i++){
		obj=childs.at(i);
		obj->Parse_UIObj_Script(os);
	}
}
void UI::Parse_Header(std::istream &is, std::string &line) {

}
void UI::Parse_Header(std::ostream &os){

}
UIObject* UI::create_UIObject() {
	return new UI();
}
UI* UI::get_cur_UI() {
	return cur_UI;
}
void UI::update() {

}
void UI::start_draw(Draw* draw) {

}
} /* namespace UI */
