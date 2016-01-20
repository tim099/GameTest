#ifndef SOURCE_CLASS_DISPLAY_UI_BUTTON_BUTTONCONTROL_H_
#define SOURCE_CLASS_DISPLAY_UI_BUTTON_BUTTONCONTROL_H_
#include "class/input/mouse/selectable/SelectableControl.h"
#include "class/display/UI/button/Button.h"

class Input;
class Draw;
namespace UI {

class ButtonControl {
public:
	ButtonControl(Input* input);
	virtual ~ButtonControl();

	void update();
	void start_draw(Draw* draw);
	SelectableControl<Button>* SC;
	std::vector<Button*>buttons;
protected:
	Input* input;
};

} /* namespace UI */

#endif /* SOURCE_CLASS_DISPLAY_UI_BUTTON_BUTTONCONTROL_H_ */
