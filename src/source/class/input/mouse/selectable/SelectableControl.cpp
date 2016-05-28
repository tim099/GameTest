#ifndef SELECTABLECONTROL_CPP_
#define SELECTABLECONTROL_CPP_
#include "class/input/mouse/selectable/SelectableControl.h"
#include "class/input/Input.h"
#include <iostream>
namespace Input{
SelectableControl::SelectableControl() {
	cur_selected=0;
	register_cur();
}
SelectableControl::~SelectableControl() {

}
void SelectableControl::push(Selectable* selectable){
	selectables.push_back(selectable);
}
void SelectableControl::update(){
	for(unsigned i=0;i<selectables.size();i++){
		selectables.at(i)->clear_state();
	}
	find_selected();
	selectables.clear();
}
Selectable* SelectableControl::find_selected(){
	Selectable* _select;
	cur_selected=0;
	Input *input=Input::get_cur_object();
	bool click=input->mouse->left_clicked();
	bool pressed=input->mouse->left_pressed();
	unsigned selectables_size=selectables.size();
	for(unsigned i=0;i<selectables_size;i++){
		_select=selectables.at(selectables_size-i-1);
		if(_select->detect_mouse_collision(input->mouse)){
			if(click){
				input->mouse->get_left_click();
				cur_selected=_select;
				_select->set_state(Selectable::state_selected,input->mouse);
			}else if(pressed){
				_select->set_state(Selectable::state_select,input->mouse);
			}else{
				_select->set_state(Selectable::state_on,input->mouse);
			}
			break;
		}
	}
	return cur_selected;
}
}
#endif /* SELECTABLECONTROL_CPP_ */
