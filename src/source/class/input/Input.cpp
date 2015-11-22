#include "class/input/Input.h"

Input::Input() {
	keyboard=new KeyBoard();
	mouse=new Mouse();
}
Input::~Input() {
	delete keyboard;
	delete mouse;
}

