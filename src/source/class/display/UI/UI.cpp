#include "class/display/UI/UI.h"
#include "class/display/draw/Draw.h"
#include "class/display/UI/UIObjectCreator.h"
#include "class/tim/string/String.h"
//#include <iostream>
namespace UI {
UI::UI() {

}
UI::UI(std::string script_path){
	Load_script(script_path);
}
UI::~UI() {

}
void UI::Parse_UIScript(std::istream &is,std::string &line){
	if (line == "ScriptPath:") {
		Tim::String::get_line(is, script_path, true, true);
		Load_script(script_path);
	}
}
void UI::Parse_UIScript(std::ostream &os){
	os<<"	"<<"ScriptPath:"<<std::endl;
	os<<"		"<<script_path<<std::endl;
	Save_script(script_path);
}
void UI::Parse_Script(std::istream &is, std::string &line) {
	if (!strcmp(line.c_str(), "CreateUIObject:")) {
		Tim::String::get_line(is, line, true, true);
		UIObject* obj = creator->create(line);
		obj->Parse_UIObj_Script(this,is,line);
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
	if (line == "Name:") {
		Tim::String::get_line(is, line, true, true);
		set_name(std::string(line));
	}
}
void UI::Parse_Header(std::ostream &os){
	os<<"	"<<"Name:"<<std::endl;
	os<<"		"<<get_name()<<std::endl;
}
void UI::update() {

}
void UI::start_draw(Display::Draw* draw) {

}
} /* namespace UI */
