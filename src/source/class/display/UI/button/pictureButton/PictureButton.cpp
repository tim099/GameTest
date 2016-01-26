#include "class/display/UI/button/pictureButton/PictureButton.h"
#include "class/display/draw/texture/DrawTexture.h"
#include "class/display/texture/texture2D/DrawData2D.h"
#include "class/display/texture/texture2D/drawDataEX/SobelData.h"
#include "class/display/texture/texture2D/drawDataEX/ColorAlter.h"
#include "class/display/window/ViewPort.h"
#include "class/display/draw/Draw.h"
#include "class/display/font/RenderString.h"
#include "class/tim/math/Math.h"
#include "class/tim/string/String.h"
#include "class/display/texture/AllTextures.h"
#include "class/input/signal/Signal.h"
#include <iostream>
namespace UI {

PictureButton::PictureButton(glm::vec2 _pos, std::string _tex_path, float width,
		float _height) {
	initialize(_pos, _tex_path, width, _height);

}
void PictureButton::initialize(glm::vec2 _pos, std::string _tex_path,
		float width, float _height) {
	set_pos(_pos);
	initialize(_tex_path, width, _height);
}
void PictureButton::initialize(std::string _tex_path, float width,
		float _height) {
	tex_path = _tex_path;
	tex2D = AllTextures::get_cur_tex(tex_path);
	height = _height;
	glm::vec2 _size = glm::vec2(width,
			width / (tex2D->get_aspect() / ViewPort::get_cur_window_aspect()));

	if (height != AutoHeight) {
		_size.y *= height;
	}
	size = _size;

	str_size = 0;
	str = 0;
}
PictureButton::~PictureButton() {
	if (str)
		delete str;
}
void PictureButton::Parse_Script(std::istream &is, std::string &line) {
	if (line == "Texture:") {
		Tim::String::get_line(is, tex_path, true, true);

		float width = 1.0f, height = 0.0f;
		Tim::String::get_line(is, line, true, true);
		if (line == "Width:") {
			is >> width;
		}
		Tim::String::get_line(is, line, true, true);
		if (line == "Height:") {
			is >> height;
		}
		initialize(tex_path, width, height);
	} else if (line == "Set_string:") {
		Tim::String::get_between(is, line, "\"");
		std::string *str = new std::string(line);
		Tim::String::get_line(is, line, true, true);
		float str_size = auto_stringSize;
		if (line == "String_size:") {
			is >> str_size;
		}
		set_string(str, str_size);
	} else if (line == "Set_signal:") {
		std::string receiver;
		std::string data;
		Tim::String::get_line(is, line, true, true);
		if (line == "Data:") {
			Tim::String::get_line(is, data, true, true);
		}
		Tim::String::get_line(is, line, true, true);
		if (line == "Receiver:") {
			Tim::String::get_line(is, receiver, true, true);
		}
		set_signal(new Signal(data, receiver));
	}

}
void PictureButton::Parse_Script(std::ostream &os) {
	os<<"	"<<"Texture:"<<std::endl;
	os<<"		"<<tex_path<<std::endl;
	os<<"	"<<"Width:"<<std::endl;
	os<<"		"<<size.x<<std::endl;
	os<<"	"<<"Height:"<<std::endl;
	os<<"		"<<height<<std::endl;
	if(str){
		os<<"	"<<"Set_string:"<<std::endl;
		os<<"\""<<*str<<"\""<<std::endl;
		os<<"	"<<"String_size:"<<std::endl;
		os<<"		"<<str_size<<std::endl;
	}
	if(signal){
		os<<"	"<<"Set_signal:"<<std::endl;
		os<<"		"<<"Data:"<<std::endl;
		os<<"			"<<signal->get_data()<<std::endl;
		os<<"		"<<"Receiver:"<<std::endl;
		os<<"			"<<signal->get_sent_to()<<std::endl;
	}
}
PictureButton::PictureButton() {
	height = 0;
	str_size = 0;
	tex2D = 0;
	str = 0;
}
UIObject* PictureButton::create_UIObject() {
	return new PictureButton();
}
void PictureButton::set_string(std::string* _str, float _str_size) {

	if (str)
		delete str;
	str = _str;
	str_size = _str_size;
	if (str_size == auto_stringSize) {
		str_size = 1.0;
		RenderString* rstr = new RenderString(*str, str_size, get_middle_pos(),
				true);
		glm::vec2 strsize = rstr->string_size();
		strsize.y *= ViewPort::get_cur_window_aspect();
		static const float edgex = 0.9, edgey = 0.8;
		glm::vec2 max_size(edgex * size.x, edgey * size.y);
		str_size = Tim::Math::fit_in_maxsize(strsize, max_size);

		delete rstr;
	}
}
void PictureButton::start_draw(Draw* draw) {
	DrawData* data = new DrawData2D(1.0, get_pos(), size.x, height);

	if (state == Selectable::state_on) {
		data->ex_datas.push_back(new ColorAlter(glm::vec3(0.3, 0.3, 0.3)));
	} else if (state == Selectable::state_selected) {
		data->ex_datas.push_back(new ColorAlter(glm::vec3(0.7, 0.7, 0.7)));
	}
	draw->push(new DrawTexture(tex2D, data));
	if (str) {
		data = draw->push_as_tex(
				new RenderString(*str, str_size, get_middle_pos(), true));
		if (state == Selectable::state_on) {
			data->ex_datas.push_back(new ColorAlter(glm::vec3(0.3, 0.3, 0.3)));
		} else if (state == Selectable::state_selected) {
			data->ex_datas.push_back(new ColorAlter(glm::vec3(0.7, 0.7, 0.7)));
		}
	}
}
} /* namespace UI */
