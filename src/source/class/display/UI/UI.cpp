#include "class/display/UI/UI.h"
#include "class/display/draw/Draw.h"
namespace UI {

UI::UI() {
	hide = false;
	button_control = 0;
}
UI::~UI() {
	if (button_control)
		delete button_control;
}
void UI::set_button_control(ButtonControl* _button_control) {
	if (button_control)
		delete button_control;
	button_control = _button_control;
}
void UI::update() {
	if (button_control)
		button_control->update();
	for(unsigned i=0;i<sub_UI.size();i++){
		if(!sub_UI.at(i)->hide)sub_UI.at(i)->update();
	}
}
void UI::start_draw(Draw* draw) {
	if (button_control)
		button_control->start_draw(draw);


	for(unsigned i=0;i<sub_UI.size();i++){
		if(!sub_UI.at(i)->hide)sub_UI.at(i)->start_draw(draw);
	}
}
} /* namespace UI */
