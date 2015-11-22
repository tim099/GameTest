#ifndef INPUT_H_
#define INPUT_H_
#include "class/input/mouse/Mouse.h"
#include "class/input/keyboard/KeyBoard.h"
class Input {
public:
	Input();
	virtual ~Input();
	KeyBoard *keyboard;
	Mouse *mouse;
};

#endif /* INPUT_H_ */
