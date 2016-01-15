#ifndef SELECTABLECONTROL_H_
#define SELECTABLECONTROL_H_
#include "class/input/mouse/selectable/Selectable.h"
#include <vector>
class Mouse;
class SelectableControl {
public:
	SelectableControl(Mouse *mou,std::vector<Selectable*>*selectables);
	virtual ~SelectableControl();
	/*
	 * check all selectable object and update their state
	 */
	void update();

	Mouse *mou;
	Selectable* cur_selected;
	std::vector<Selectable*>*selectables;
};

#endif /* SELECTABLECONTROL_H_ */
