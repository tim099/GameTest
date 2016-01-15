#include "class/display/UI/button/ButtonControl.h"

namespace UI {

ButtonControl::ButtonControl(Mouse *_mou) {
	SC=new SelectableControl(_mou,&buttons);
}
ButtonControl::~ButtonControl() {
	delete SC;
	for(unsigned i=0;i<buttons.size();i++){
		delete buttons.at(i);
	}
}
inline Button* ButtonControl::get_button(int i){
	return (Button*)buttons.at(i);
}
void ButtonControl::update(){
	SC->update();
}
} /* namespace UI */
