#ifndef SOURCE_CLASS_DISPLAY_UI_BUTTON_BUTTON_H_
#define SOURCE_CLASS_DISPLAY_UI_BUTTON_BUTTON_H_

#include "class/tim/geometry/2D/RectP2D.h"
#include "class/input/mouse/selectable/Selectable.h"
namespace UI {

class Button : public Selectable{
public:
	Button(Tim::RectP2D* select_range);
	virtual ~Button();
	virtual bool detect_mouse_collision(Mouse *mou);
protected:
	Tim::RectP2D* select_range;
};

} /* namespace UI */

#endif /* SOURCE_CLASS_DISPLAY_UI_BUTTON_BUTTON_H_ */
