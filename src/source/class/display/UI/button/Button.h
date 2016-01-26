#ifndef SOURCE_CLASS_DISPLAY_UI_BUTTON_BUTTON_H_
#define SOURCE_CLASS_DISPLAY_UI_BUTTON_BUTTON_H_
#include <glm/vec2.hpp>
#include "class/display/UI/UIObject.h"
class Draw;
class Signal;
namespace UI {

class Button: public UIObject {
public:
	Button();
	virtual ~Button();

	virtual void selected(Mouse* mou);

	void set_signal(Signal* signal);
	Signal* get_signal() const;

	virtual std::string get_type_name()const{
		return "Button";
	}
protected:
	virtual void update();

	/*
	 * provide for inherit class from button
	 * updated every frame
	 */
	virtual void update_button();


	Signal* signal;
};

} /* namespace UI */

#endif /* SOURCE_CLASS_DISPLAY_UI_BUTTON_BUTTON_H_ */
