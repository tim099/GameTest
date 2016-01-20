#ifndef SOURCE_CLASS_DISPLAY_UI_BUTTON_BUTTON_H_
#define SOURCE_CLASS_DISPLAY_UI_BUTTON_BUTTON_H_
#include <glm/glm.hpp>
#include "class/input/mouse/selectable/Selectable.h"
class Draw;
class Signal;
namespace UI {

class Button: public Selectable {
public:
	Button();
	virtual ~Button();
	virtual bool detect_mouse_collision(Mouse *mou);
	virtual void start_draw(Draw* draw)=0;

	virtual void mouse_on();
	virtual void selected();
	virtual void update();

	void set_signal(Signal* signal);
	Signal* get_signal()const;
	void initial(glm::vec2 pos, glm::vec2 size);
	/*
	 * return the middle position of the button
	 */
	glm::vec2 get_middle_pos()const;
protected:
	/*
	 * provide for inherit class from button
	 * updated every frame
	 */
	virtual void button_update();
	glm::vec2 pos,size;
	Signal* signal;
};

} /* namespace UI */

#endif /* SOURCE_CLASS_DISPLAY_UI_BUTTON_BUTTON_H_ */
