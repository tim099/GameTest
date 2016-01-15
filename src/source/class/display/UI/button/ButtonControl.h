#ifndef SOURCE_CLASS_DISPLAY_UI_BUTTON_BUTTONCONTROL_H_
#define SOURCE_CLASS_DISPLAY_UI_BUTTON_BUTTONCONTROL_H_
#include "class/input/mouse/selectable/SelectableControl.h"
#include "class/display/UI/button/Button.h"

class Mouse;
namespace UI {

class ButtonControl {
public:
	ButtonControl(Mouse *mou);
	virtual ~ButtonControl();

	inline Button* get_button(int i);


	void update();
	SelectableControl* SC;
	std::vector<Selectable*>buttons;
};

} /* namespace UI */

#endif /* SOURCE_CLASS_DISPLAY_UI_BUTTON_BUTTONCONTROL_H_ */
