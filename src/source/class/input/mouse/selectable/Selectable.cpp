#include "class/input/mouse/selectable/Selectable.h"
#include "class/input/mouse/selectable/SelectableControl.h"
namespace Input{
Selectable::Selectable() {
	state=state_null;
}
Selectable::~Selectable() {

}
void Selectable::detect_selection(){
	SelectableControl::get_cur_object()->push(this);
}
void Selectable::mouse_on(Mouse* mou){

}
void Selectable::select(Mouse* mou){

}
void Selectable::selected(Mouse* mou){

}
void Selectable::clear_state(){
	state=state_null;
}
void Selectable::set_state(int _state,Mouse* mou){
	state=_state;
	if(state==state_on){
		mouse_on(mou);
	}else if(state==state_select){
		select(mou);
	}else if(state==state_selected){
		selected(mou);
	}
}
int Selectable::get_state()const{
	return state;
}
}
