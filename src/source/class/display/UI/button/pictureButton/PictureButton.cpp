#include "class/display/UI/button/pictureButton/PictureButton.h"
#include "class/display/draw/texture/DrawTexture.h"
#include "class/display/texture/texture2D/DrawData2D.h"
#include "class/display/texture/texture2D/drawDataEX/SobelData.h"
#include "class/display/texture/texture2D/drawDataEX/ColorAlter.h"
#include "class/display/window/ViewPort.h"
#include "class/display/draw/Draw.h"
#include "class/display/font/RenderString.h"
#include "class/tim/math/Math.h"
#include "class/display/texture/AllTextures.h"
#include "class/input/signal/Signal.h"
#include <iostream>
namespace UI {

PictureButton::PictureButton(math::vec2<float> _pos, std::string _tex_path, float width,
		float _height) {
	init(_pos, _tex_path, width, _height);

}
void PictureButton::init(math::vec2<float> _pos, std::string _tex_path,
		float width, float _height) {
	set_pos(_pos);
	set_texture(_tex_path, width, _height);
}
void PictureButton::set_texture(std::string _tex_path, float width,
		float _height) {
	tex_path = _tex_path;
	tex2D = Display::AllTextures::get_cur_tex(tex_path);
	height = _height;
	glm::vec2 _size = glm::vec2(width,
			width / (tex2D->get_aspect() / Display::ViewPort::get_cur_window_aspect()));

	if (height != AutoHeight) {
		_size.y *= height;
	}
	size = _size;
}
void PictureButton::set_texture() {
	set_texture(tex_path, size.x, height);
}
PictureButton::~PictureButton() {
	if (str)
		delete str;
}

UIObject* PictureButton::copy_UIObject() {
	PictureButton *copy = new PictureButton();
	copy->init(get_pos(), tex_path, size.x, height);
	if (get_parent())
		get_parent()->push_child(copy);
	//if(str)copy->set_string(new std::string(*str),font_size);
	return copy;
}

void PictureButton::Parse_UIScript(std::istream &is, std::string &line) {
	if (line == "#create_end") {

	} else if (line == "Set_string:") {
		Tim::String::get_between(is, line, "\"");
		std::string *str = new std::string(line);
		Tim::String::get_line(is, line, true, true);
		float str_size = auto_Size;
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
		set_signal(new Input::Signal(data, receiver));
	}else{
		Parse_texture(is,line);
	}

}
void PictureButton::Parse_texture(std::istream &is, std::string &line) {
	if (line == "Texture:") {
		Tim::String::get_line(is, tex_path, true, true);
		size.x = 1.0f;
		height = 0.0f;
	} else if (line == "Width:") {
		is >> size.x;
	} else if (line == "Height:") {
		is >> height;
		set_texture();
	}
}
void PictureButton::Parse_texture(std::ostream &os) {
	os << "	" << "Texture:" << std::endl;
	os << "		" << tex_path << std::endl;
	os << "	" << "Width:" << std::endl;
	os << "		" << size.x << std::endl;
	os << "	" << "Height:" << std::endl;
	os << "		" << height << std::endl;
}
void PictureButton::Parse_UIScript(std::ostream &os) {
	Parse_texture(os);
	if (str) {
		os << "	" << "Set_string:" << std::endl;
		os << "\"" << *str << "\"" << std::endl;
		os << "	" << "String_size:" << std::endl;
		os << "		" << font_size << std::endl;
	}
	if (signal) {
		os << "	" << "Set_signal:" << std::endl;
		os << "		" << "Data:" << std::endl;
		os << "			" << signal->get_data() << std::endl;
		os << "		" << "Receiver:" << std::endl;
		os << "			" << signal->get_sent_to() << std::endl;
	}
}
PictureButton::PictureButton() {
	height = 0;
	font_size = 0;
	tex2D = 0;
	str = 0;
}
UIObject* PictureButton::create_UIObject() {
	return new PictureButton();
}
void PictureButton::set_string(std::string* _str, float _font_size) {
	if (str) {
		delete str;
	}

	str = _str;
	font_size = _font_size;
	if (font_size == auto_Size) {

		static const float edgex = 0.9, edgey = 0.8;
		math::vec2<float> max_size(edgex * size.x, edgey * size.y);

		font_size = 1.0;
		Display::RenderString* rstr = new Display::RenderString(*str, font_size);
		rstr->auto_char_size(max_size);
		font_size = rstr->size;
		delete rstr;
	}
}
void PictureButton::start_draw(Display::Draw* draw) {
	Display::DrawData* data = new Display::DrawData2D(1.0, get_pos(), size.x, height);

	if (state == Selectable::state_on) {
		data->ex_datas.push_back(new Display::drawDataEX::ColorAlter(glm::vec3(0.3, 0.3, 0.3)));
	} else if (state == Selectable::state_selected) {
		data->ex_datas.push_back(new Display::drawDataEX::ColorAlter(glm::vec3(0.7, 0.7, 0.7)));
	}
	draw->push(new Display::DrawTexture(tex2D, data));

	//return;
	if (str) {
		data = draw->push_as_tex(
				new Display::RenderString(*str, font_size, get_middle_pos(), true));
		if (state == Selectable::state_on) {
			data->ex_datas.push_back(new Display::drawDataEX::ColorAlter(glm::vec3(0.3, 0.3, 0.3)));
		} else if (state == Selectable::state_selected) {
			data->ex_datas.push_back(new Display::drawDataEX::ColorAlter(glm::vec3(0.7, 0.7, 0.7)));
		}
	}
}
} /* namespace UI */
