#ifndef SOURCE_CLASS_DISPLAY_UI_UI_H_
#define SOURCE_CLASS_DISPLAY_UI_UI_H_
#include <vector>
#include "class/display/UI/button/ButtonControl.h"

class Draw;
namespace UI {
class UI {
public:
	UI();
	virtual ~UI();

	void update();
	void set_button_control(ButtonControl* button_control);
	void start_draw(Draw* draw);

	bool hide;
protected:
	ButtonControl* button_control;
	std::vector<UI*>sub_UI;
};

} /* namespace UI */

#endif /* SOURCE_CLASS_DISPLAY_UI_UI_H_ */
