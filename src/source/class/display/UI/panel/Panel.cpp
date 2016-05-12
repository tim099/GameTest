#include "class/display/UI/panel/Panel.h"
#include "class/display/draw/texture/DrawTexture.h"
#include "class/display/texture/texture2D/DrawData2D.h"
#include "class/display/texture/texture2D/drawDataEX/SobelData.h"
#include "class/display/texture/texture2D/drawDataEX/ColorAlter.h"
#include "class/display/window/ViewPort.h"
#include "class/display/draw/Draw.h"
#include "class/display/texture/AllTextures.h"
namespace UI {
Panel::Panel() {
	tex2D = 0;
	height = 0;
}
Panel::Panel(glm::vec2 _pos,std::string _tex_path, float _width, float _height) {
	init(_pos, _tex_path, _width, _height);
}
void Panel::set_texture(std::string _tex_path, float width, float _height) {
	tex_path=_tex_path;
	tex2D=Display::AllTextures::get_cur_tex(tex_path);
	height = _height;
	glm::vec2 _size = glm::vec2(width,
			width / (tex2D->get_aspect() / Display::ViewPort::get_cur_window_aspect()));

	if (height != AutoHeight) {
		_size.y *= height;
	}
	size = _size;
}
void Panel::init(glm::vec2 _pos,std::string _tex_path, float width,
		float _height) {
	set_pos(_pos);
	set_texture(_tex_path, width, _height);
}
void Panel::Parse_UIScript(std::istream &is, std::string &line) {
	if (line == "#create_end") {
		set_texture(tex_path, size.x, height);
	} else if (line == "Texture:") {
		Tim::String::get_line(is, tex_path, true, true);
		size.x=1.0f;height=0.0f;
	}else if(line == "Width:"){
		is >> size.x;
	}else if(line == "Height:"){
		is >> height;
	}
}
void Panel::Parse_UIScript(std::ostream &os) {
	os<<"	"<<"Texture:"<<std::endl;
	os<<"		"<<tex_path<<std::endl;
	os<<"	"<<"Width:"<<std::endl;
	os<<"		"<<size.x<<std::endl;
	os<<"	"<<"Height:"<<std::endl;
	os<<"		"<<height<<std::endl;
}
Panel::~Panel() {

}
UIObject* Panel::create_UIObject() {
	return new Panel();
}
void Panel::start_draw(Display::Draw* draw) {
	Display::DrawData* data = new Display::DrawData2D(1.0, get_pos(), size.x, height);
	if(check_mode(UI::Mode::EDIT)){
		if (state == Selectable::state_on) {
			data->ex_datas.push_back(
					new Display::drawDataEX::ColorAlter(glm::vec3(0.3, 0.3, 0.3)));
		} else if (state == Selectable::state_selected) {
			data->ex_datas.push_back(
					new Display::drawDataEX::ColorAlter(glm::vec3(0.7, 0.7, 0.7)));
		}
	}
	draw->push(new Display::DrawTexture(tex2D, data));
}
void Panel::update() {

	update_panel();
}
void Panel::update_panel() {

}
} /* namespace UI */
