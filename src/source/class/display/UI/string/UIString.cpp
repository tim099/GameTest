#include "class/display/UI/string/UIString.h"
#include "class/display/draw/Draw.h"
#include "class/display/font/RenderString.h"
#include "class/input/signal/Receiver.h"
#include "class/input/Input.h"
#include "class/input/mouse/Mouse.h"
#include "class/display/texture/texture2D/drawDataEX/ColorAlter.h"
#include <iostream>
namespace UI {
UIString* UIString::cur_input_str=0;
UIString::UIString() {
	str = 0;
	font_size = 0.0;
	input_mode=false;
	insert_at=-1;
	cur_insert_at=0;
	blink=0;
}
UIString::~UIString() {
	if (str)
		delete str;
}
std::string UIString::get_string(){
	return std::string(*str);
}
void UIString::set_string(std::string _str){
	*str=_str;
}
void UIString::initialize(std::string* _str, float _font_size) {
	str = _str;
	cur_insert_at=str->size();
	font_size = _font_size;
	size = glm::vec2(1,2)*RenderString::string_size(str,font_size);
}
UIObject* UIString::create_UIObject() {
	return new UIString();
}
void UIString::Parse_UIScript(std::istream &is, std::string &line) {
	if (line == "String:") {
		Tim::String::get_between(is, line, "\"");
		std::string *str = new std::string(line);
		Tim::String::get_line(is, line, true, true);
		float str_size = 0.0f;
		if (line == "String_size:") {
			is >> str_size;
		}
		initialize(str, str_size);
	}else if(line == "#EnableInputMode"){
		input_mode=true;
		enable_input();
	}
}
void UIString::Parse_UIScript(std::ostream &os) {
	os << "	" << "String:" << std::endl;
	os << "\"" << *str << "\"" << std::endl;
	os << "	" << "String_size:" << std::endl;
	os << "		" << font_size << std::endl;
	if(input_mode){
		os << "	" << "#EnableInputMode" << std::endl;
	}
}
void UIString::start_draw(Draw* draw) {
	if (str) {
		RenderString* rstr=new RenderString(*str, font_size, get_pos(), false);
		DrawData* data=draw->push_as_tex(rstr);
		if(input_mode&&cur_input_str==this){
			rstr->insert_at=insert_at;
			data->ex_datas.push_back(new ColorAlter(glm::vec3(0.2, 0.2, 0.2)));
		}
	}
}
void UIString::update() {
	if(receiver){
		Signal *sig=receiver->get_signal();
		if(sig){
			*str=sig->get_data();
		}
	}
	if(Input::get_cur_object()->mouse->left_clicked()){
		if (get_state() == state_select) {
			enable_input();
		}else{
			disable_input();
		}
	}

	if(input_mode&&cur_input_str==this){
		KeyBoard* keyboard=Input::get_cur_object()->keyboard;
		if(keyboard->get(KeyCode::Left)){
			if(cur_insert_at>0)cur_insert_at--;
		}else if(keyboard->get(KeyCode::Right)){
			if(cur_insert_at<(int)str->size())cur_insert_at++;
		}else if(keyboard->get(KeyCode::BackSpace)){
			if(str->size()>0){
				std::string tmp=str->substr(cur_insert_at,str->size());
				str->resize(cur_insert_at-1);
				//str->erase(cur_insert_at-1);
				*str+=tmp;
				cur_insert_at--;
				size = glm::vec2(1,2)*RenderString::string_size(str,font_size);
			}
		}else{
			unsigned c=keyboard->get_char();
			if(c!=0&&c<256){
				std::string tmp=str->substr(cur_insert_at,str->size());
				//str->erase(cur_insert_at);
				str->resize(cur_insert_at);
				str->push_back((char)c);
				*str+=tmp;
				cur_insert_at++;
				size = glm::vec2(1,2)*RenderString::string_size(str,font_size);
			}
		}
		keyboard->clear_keys();
		keyboard->clear_chars();

		if(blink>60){
			blink=0;
		}else{
			blink++;
		}
		if(blink<40){
			insert_at=cur_insert_at;
		}else{
			insert_at=-1;
		}
	}
}
} /* namespace UI */
