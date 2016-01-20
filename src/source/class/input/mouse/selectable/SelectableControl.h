#ifndef SELECTABLECONTROL_H_
#define SELECTABLECONTROL_H_
#include "class/input/mouse/selectable/Selectable.h"
#include <vector>
class Input;
template <class selectClass>
class SelectableControl {
public:
	SelectableControl(Input *input,std::vector<selectClass*>*selectables);
	virtual ~SelectableControl();
	/*
	 * update all selectable object
	 */
	void update();
	/*
	 *find current selected object
	 */
	selectClass* find_selected();

	Input *input;
	selectClass* cur_selected;
	std::vector<selectClass*>*selectables;
};
#include "class/input/mouse/selectable/SelectableControl.cpp"
#endif /* SELECTABLECONTROL_H_ */
