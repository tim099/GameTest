#include "class/input/mouse/selectable/Selectable.h"

Selectable::Selectable() {
	state=Selectable_null;
}
Selectable::~Selectable() {

}
void Selectable::update(){

}
void Selectable::mouse_on(){

}
void Selectable::selected(){

}
void Selectable::set_state(int _state){
	state=_state;
	if(state==Selectable_on){
		mouse_on();
	}else if(state==Selectable_selected){
		selected();
	}
}
