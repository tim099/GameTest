#ifndef SOURCE_CLASS_DISPLAY_UI_UI_H_
#define SOURCE_CLASS_DISPLAY_UI_UI_H_
#include <vector>
#include "class/input/mouse/selectable/SelectableControl.h"

namespace UI {

class UI {
public:
	UI();
	virtual ~UI();


	bool hide;
	std::vector<UI*>sub_UI;
};

} /* namespace UI */

#endif /* SOURCE_CLASS_DISPLAY_UI_UI_H_ */
