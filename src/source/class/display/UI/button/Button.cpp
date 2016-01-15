#include "class/display/UI/button/Button.h"
#include "class/input/mouse/Mouse.h"
namespace UI {

Button::Button(Tim::RectP2D* _select_range) {
	select_range=_select_range;
}
Button::~Button() {
	delete select_range;
}
bool Button::detect_mouse_collision(Mouse *mou){
	return select_range->coincide(mou->get_tex_space_pos());
}
} /* namespace UI */
