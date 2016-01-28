#include "class/display/UI/UIObject.h"
#include "class/input/mouse/Mouse.h"
#include "class/display/UI/UI.h"
#include "class/tim/string/String.h"
#include <iostream>
namespace UI {

UIObject::UIObject() {
	parent = 0;
	mode = 0;
	hide = false;
	name = "default";
}
UIObject::~UIObject() {
	if (parent) {
		parent->remove_child(this);
	}
	clear_child();
}
void UIObject::Parse_UIObj_Script(std::istream &is, std::string &line) {
	UI* cur_UI = UI::get_cur_UI();
	while (Tim::String::get_line(is, line, true, true)) {
		if (line == "#create_end") {
			break;
		} else if (line == "Parent:") {
			Tim::String::get_line(is, line, true, true);
			UIObject* parent = cur_UI->get_child(line);
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
			set_pos(tpos);
		} else {
			Parse_Script(is, line);
		}
	}

}
void UIObject::Parse_UIObj_Script(std::ostream &os) {
	//UI* cur_UI=UI::get_cur_UI();
	os << "CreateUIObject:" << std::endl;
	os << "		" << get_type_name() << std::endl;
	os << "	" << "Name:" << std::endl;
	os << "		" << get_name() << std::endl;
	os << "	" << "Position:" << std::endl;
	os << "		" << pos.x << " " << pos.y << std::endl;

	Parse_Script(os);

	os << "	" << "Parent:" << std::endl;
	os << "		" << get_parent()->get_name() << std::endl;
	os << "#create_end" << std::endl << std::endl;
	UIObject* obj;
	for (unsigned i = 0; i < childs.size(); i++) {
		obj = childs.at(i);
		obj->Parse_UIObj_Script(os);
	}
}
void UIObject::Parse_Script(std::istream &is, std::string &line) {

}
void UIObject::Parse_Script(std::ostream &os) {

}
UIObject* UIObject::get_child(std::string name) {
	if (name == get_name())
		return this;
	UIObject* find;
	for (unsigned i = 0; i < childs.size(); i++) {
		find = childs.at(i)->get_child(name);
		if (find)
			return find;
	}
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
void UIObject::initial(glm::vec2 _pos, glm::vec2 _size) {
	set_pos(_pos);
	size = _size;
}
glm::vec2 UIObject::get_middle_pos() const {
	return get_pos() + glm::vec2(0.5 * size.x, -0.5 * size.y);
}
//==========SelectableRec implement========
glm::vec2 UIObject::get_rec_pos() const {
	return get_pos();
}
glm::vec2 UIObject::get_rec_size() const {
	return size;
}
//========================================
void UIObject::draw_UIObject(Draw* draw) {
	if (hide)
		return;
	start_draw(draw);
	for (unsigned i = 0; i < childs.size(); i++) {
		childs.at(i)->draw_UIObject(draw);
	}
}
void UIObject::start_draw(Draw* draw) {

}
void UIObject::update_UIObject() {
	if (hide)
		return;

	detect_selection();
	if ((check_mode(Mode::EDIT))&&get_state() == state_select) {
		set_pos(get_pos()+ 0.5f
					* Mouse::get_cur_mouse()->get_screen_pos_delta());
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
	for (unsigned i = 0; i < childs.size(); i++) {
		if (child == childs.at(i)) {
			childs.at(i)->clear_parent();
			childs.at(i) = childs.back();
			childs.pop_back();
			return;
		}
	}
	std::cout << this << "remove child fail!!can't find the child" << std::endl;
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
void UIObject::set_pos(glm::vec2 _pos) {
	pos = _pos;
	if (parent)
		pos -= parent->get_pos();
}
glm::vec2 UIObject::get_pos() const {
	if (parent) {
		return pos + parent->get_pos();
	}
	return pos;
}
} /* namespace UI */
