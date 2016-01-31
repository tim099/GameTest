#include "class/display/UI/string/UIString.h"
#include "class/display/draw/Draw.h"
#include "class/display/font/RenderString.h"
#include "class/input/signal/Receiver.h"
#include "class/input/Input.h"
#include "class/display/texture/texture2D/drawDataEX/ColorAlter.h"
#include <iostream>
namespace UI {

UIString::UIString() {
	str = 0;
	font_size = 0.0;
	input_mode=false;
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
	font_size = _font_size;

	RenderString* rstr = new RenderString(*str, font_size);
	font_size = rstr->size;
	size = rstr->string_size();
	delete rstr;
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
		DrawData* data=draw->push_as_tex(new RenderString(*str, font_size, get_pos(), false));
		if(input_mode){
			data->ex_datas.push_back(new ColorAlter(glm::vec3(0.4, 0.4, 0.4)));
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
	if(input_mode){
		KeyBoard* keyboard=Input::get_cur_object()->keyboard;
		if(keyboard->get(KeyCode::BackSpace)){
			if(str->size()>0){
				str->resize(str->size()-1);
			}
		}else{
			unsigned c=keyboard->get_char();
			if(c!=0&&c<256){
				str->push_back((char)c);
			}
		}
		keyboard->clear_keys();
		keyboard->clear_chars();
	}
}
} /* namespace UI */
