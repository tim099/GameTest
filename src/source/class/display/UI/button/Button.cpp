#include "class/display/UI/button/Button.h"
#include "class/input/mouse/Mouse.h"
#include "class/tim/geometry/2D/RectP2D.h"
#include "class/input/signal/Signal.h"
namespace UI {

Button::Button() {
	signal=0;
}
Button::~Button() {
	if(signal)delete signal;
}
void Button::initial(glm::vec2 _pos, glm::vec2 _size){
	pos=_pos;
	size=_size;
}
bool Button::detect_mouse_collision(Mouse *mou){
	return Tim::RectP2D::coincide(mou->get_tex_space_pos(),pos,pos+glm::vec2(size.x,-size.y));
}
glm::vec2 Button::get_middle_pos()const{
	return pos+glm::vec2(0.5*size.x,-0.5*size.y);
}
void Button::mouse_on(){

}
void Button::selected(){

}
void Button::set_signal(Signal* _signal){
	if(signal)delete signal;
	signal=_signal;
}
Signal* Button::get_signal()const{
	return signal;
}
void Button::update(){
	state=Selectable_null;
	button_update();
}
void Button::button_update(){

}
} /* namespace UI */
