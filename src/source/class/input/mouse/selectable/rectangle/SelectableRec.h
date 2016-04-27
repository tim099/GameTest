#ifndef SOURCE_CLASS_INPUT_MOUSE_SELECTABLE_RECTANGLE_SELECTABLEREC_H_
#define SOURCE_CLASS_INPUT_MOUSE_SELECTABLE_RECTANGLE_SELECTABLEREC_H_
#include <glm/vec2.hpp>
#include "class/input/mouse/selectable/Selectable.h"
namespace Input{
class Mouse;
class SelectableRec: public Selectable {
public:
	SelectableRec();
	virtual ~SelectableRec();
	virtual bool detect_mouse_collision(Mouse *mou);
protected:
	virtual glm::vec2 get_rec_pos()const=0;
	virtual glm::vec2 get_rec_size()const=0;
};
}
#endif /* SOURCE_CLASS_INPUT_MOUSE_SELECTABLE_RECTANGLE_SELECTABLEREC_H_ */
