#include "class/display/UI/button/Button.h"
#include "class/input/mouse/Mouse.h"
#include "class/tim/geometry/2D/RectP2D.h"
#include "class/input/signal/Signal.h"

#include "class/input/Input.h"
#include <iostream>
//#include "class/tim/math/Math.h"
namespace UI {

Button::Button() {
	signal=0;
}
Button::~Button() {
	if(signal)delete signal;
}
void Button::selected(Mouse* mou){
	if(get_signal()){
		Input::get_cur_input()->sent_signal(get_signal());
	}
}
void Button::set_signal(Signal* _signal){
	if(signal)delete signal;
	signal=_signal;
}
Signal* Button::get_signal()const{
	return signal;
}
void Button::update(){
	if(get_state()==state_select){
		set_pos(get_pos()+0.5f*Mouse::get_cur_mouse()->get_screen_pos_delta());
	}
	update_button();
}
void Button::update_button(){

}
} /* namespace UI */
