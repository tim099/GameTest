#ifndef SELECTABLECONTROL_CPP_
#define SELECTABLECONTROL_CPP_
#include "class/input/mouse/selectable/SelectableControl.h"
#include "class/input/Input.h"
template <class selectClass>
SelectableControl<selectClass>::SelectableControl(Input *_input,std::vector<selectClass*>*_selectables) {
	input=_input;
	cur_selected=0;
	selectables=_selectables;
}
template <class selectClass>
SelectableControl<selectClass>::~SelectableControl() {

}
template <class selectClass>
void SelectableControl<selectClass>::update(){
	for(unsigned i=0;i<selectables->size();i++){
		selectables->at(i)->update();
	}

}
template <class selectClass>
selectClass* SelectableControl<selectClass>::find_selected(){
	selectClass* select;
	cur_selected=0;
	bool click=input->mouse->get_left_click();
	for(unsigned i=0;i<selectables->size();i++){
		select=selectables->at(i);
		if(select->detect_mouse_collision(input->mouse)){
			if(click){
				cur_selected=select;
				select->set_state(Selectable_selected);
			}else{
				select->set_state(Selectable_on);
			}

			break;
		}
	}
	return cur_selected;
}
#endif /* SELECTABLECONTROL_CPP_ */
