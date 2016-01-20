#include "class/display/UI/button/ButtonControl.h"
#include "class/input/Input.h"
namespace UI {

ButtonControl::ButtonControl(Input* _input) {
	input=_input;
	SC=new SelectableControl<Button>(input,&buttons);
}
ButtonControl::~ButtonControl() {
	delete SC;
	for(unsigned i=0;i<buttons.size();i++){
		delete buttons.at(i);
	}
}
void ButtonControl::update(){
	SC->update();
	Button* selected=SC->find_selected();
	if(selected){
		if(selected->get_signal()){
			input->sent_signal(selected->get_signal());
		}
	}
}
void ButtonControl::start_draw(Draw* draw){
	for(unsigned i=0;i<buttons.size();i++){
		buttons.at(i)->start_draw(draw);
	}
}
} /* namespace UI */
