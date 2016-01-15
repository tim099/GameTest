#include "class/input/mouse/selectable/SelectableControl.h"
#include "class/input/mouse/Mouse.h"
SelectableControl::SelectableControl(Mouse *_mou,std::vector<Selectable*>*_selectables) {
	mou=_mou;
	cur_selected=0;
	selectables=_selectables;
}
SelectableControl::~SelectableControl() {
/*
 * not handle delete of the objects
 */
}
void SelectableControl::update(){
	Selectable* select;
	cur_selected=0;
	for(unsigned i=0;i<selectables->size();i++){
		select=selectables->at(i);
		if(select->detect_mouse_collision(mou)){
			if(mou->get_left_click()){
				cur_selected=select;
				select->selected();
			}else{
				select->mouse_on();
			}
			break;
		}
	}
}
