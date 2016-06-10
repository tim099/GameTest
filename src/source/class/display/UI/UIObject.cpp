#include "class/display/UI/UIObject.h"
#include "class/input/mouse/Mouse.h"
#include "class/display/UI/UI.h"
#include "class/input/Input.h"
#include "class/input/signal/Receiver.h"
#include "class/display/UI/UIObjectCreator.h"
#include <iostream>
namespace UI {

UIObject::UIObject() {
	parent = 0;
	mode = 0;
	hide = false;
	name = "default_UIObject";
	receiver=0;
	creator = UIObjectCreator::get_cur_object();
}
UIObject::~UIObject() {
	if (parent) {
		parent->remove_child(this);
	}
	if (receiver) {
		Input::Input::get_cur_object()->remove_receiver(receiver->get_name());
	}
	clear_child();
}
void UIObject::Parse_UIObj_Script(UIObject* cur_root,std::istream &is, std::string &line) {
	while (Tim::String::get_line(is, line, true, true)) {
		if (line == "#create_end") {
			Parse_UIScript(is, line);//tell UIOBject to end parsing!!
			if(!get_parent()&&cur_root){
				cur_root->push_child(this);
			}
			break;
		} else if (line == "Parent:") {
			Tim::String::get_line(is, line, true, true);
			UIObject* parent = cur_root->get_child(line);
			if (parent) {
				parent->push_child(this);
			} else {
				std::cerr << "can't find UI's Parent:" << line << std::endl;
			}
		} else if (line == "Name:") {
			Tim::String::get_line(is, line, true, true);
			set_name(line);
		} else if (line == "Position:") {
			glm::vec2 tpos;
			is >> tpos.x;
			is >> tpos.y;
			set_relative_pos(tpos);
		}else if (line == "Set_receiver:") {
			Tim::String::get_line(is, line, true, true);
			set_receiver(line);
		} else {
			Parse_UIScript(is, line);
		}
	}

}
void UIObject::Parse_UIObj_Script(std::ostream &os) {
	//UI* cur_UI=UI::get_cur_UI();
	os << "CreateUIObject:" << std::endl;
	os << "		" << get_type() << std::endl;
	os << "	" << "Name:" << std::endl;
	os << "		" << get_name() << std::endl;
	os << "	" << "Position:" << std::endl;
	os << "		" << pos.x << " " << pos.y << std::endl;

	Parse_UIScript(os);

	os << "	" << "Parent:" << std::endl;
	os << "		" << get_parent()->get_name() << std::endl;
	if (receiver) {
		os << "	" << "Set_receiver:" << std::endl;
		os << "		" << receiver->get_name() << std::endl;
	}
	os << "#create_end" << std::endl << std::endl;



	if(!save_child()){
		return;
	}
	UIObject* obj;
	for (unsigned i = 0; i < childs.size(); i++) {
		obj = childs.at(i);
		obj->Parse_UIObj_Script(os);
	}
}
void UIObject::Parse_UIScript(std::istream &is, std::string &line) {

}
void UIObject::Parse_UIScript(std::ostream &os) {

}
UIObject* UIObject::search_root(std::string name){
	return get_root()->get_child(name);
}
UIObject* UIObject::get_child(std::string name) {
	if (name == get_name())
		return this;
	UIObject* find;
	for (unsigned i = 0; i < childs.size(); i++) {
		find = childs.at(i)->get_child(name);
		if (find){
			//std::cout<<"UIObject : find "<<name<<std::endl;
			return find;
		}
	}
	//std::cout<<"UIObject : not find "<<name<<std::endl;
	return 0;
}
std::string UIObject::get_name() const {
	return name;
}
void UIObject::set_name(std::string _name) {
	name = _name;
}
void UIObject::clear_child() {
	while (!childs.empty()) {
		delete childs.back();
	}
	//childs.clear();//just for safety, all child should already removed
}
void UIObject::draw_UIObject(Display::Draw* draw) {
	if (hide)
		return;
	start_draw(draw);
	for (unsigned i = 0; i < childs.size(); i++) {
		//std::cout<<"UI object "<<get_name()<<" draw child : "<<childs.at(i)->get_name()<<std::endl;
		childs.at(i)->draw_UIObject(draw);
	}
}
void UIObject::start_draw(Display::Draw* draw) {

}
void UIObject::update_UIObject() {
	if (hide)
		return;

	detect_selection();
	if ((check_mode(Mode::EDIT))&&get_state() == state_select) {
		set_pos(get_pos()+ 0.5f
					* Input::Mouse::get_cur_mouse()->get_screen_pos_delta());
	}


	update();
	for (unsigned i = 0; i < childs.size(); i++) {
		childs.at(i)->update_UIObject();
	}
}
void UIObject::update() {

}
void UIObject::clear_parent() {
	parent = 0;
}
void UIObject::set_parent(UIObject* _parent) {
	if (parent) {
		parent->remove_child(this);
	}
	parent = _parent;
}
void UIObject::remove_child(UIObject* child) {
	if(child==childs.back()){
		childs.back()->clear_parent();
		childs.pop_back();
		return;
	}
	for (unsigned i = 0; i < childs.size(); i++) {
		if (child == childs.at(i)) {
			childs.at(i)->clear_parent();
			childs.at(i) = childs.back();
			childs.pop_back();
			return;
		}
	}
	std::cout << get_name() << ": remove child fail!!can't find the child" << std::endl;
}
void UIObject::push_child(UIObject* child) {
	if (child == this || child == get_root()) {
		std::cout << "can't set child,this will make a cycle in UIObject"
				<< std::endl;
	}
	child->set_parent(this);
	childs.push_back(child);
}
void UIObject::Enable_Mode(int flag) {
	mode |= flag;
	for (unsigned i = 0; i < childs.size(); i++) {
		childs.at(i)->Enable_Mode(flag);
	}
}
void UIObject::Disable_Mode(int flag) {
	mode &= (~flag);
	for (unsigned i = 0; i < childs.size(); i++) {
		childs.at(i)->Disable_Mode(flag);
	}
}
bool UIObject::check_mode(int flag)const{
	if((mode&flag)!=0)return true;
	return false;
}
UIObject* UIObject::get_parent() const {
	return parent;
}
UIObject* UIObject::get_root() {
	if (parent) {
		return parent->get_root();
	}
	return this;
}
void UIObject::set_receiver(std::string receiver_name) {
	if (receiver) {
		Input::Input::get_cur_object()->remove_receiver(receiver->get_name());
	}
	receiver = new Input::Receiver(receiver_name);
	Input::Input::get_cur_object()->push_receiver(receiver);
}
UIObject* UIObject::copy_UIObject(){
	std::cerr<<"UIObject:"<<get_type()<<"not implement UIObject::copy_UIObject()"<<std::endl;
	return 0;
}


} /* namespace UI */
