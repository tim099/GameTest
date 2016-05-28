#ifndef SELECTABLECONTROL_H_
#define SELECTABLECONTROL_H_
#include "class/input/mouse/selectable/Selectable.h"
#include "class/controller/Controller.h"
#include "class/tim/globalObject/GlobalObject.h"
#include <vector>
namespace Input{
class Input;

class SelectableControl : public Controller,public Tim::GlobalObject<SelectableControl>{
	//static SelectableControl* cur_SelectableControl;
public:
	SelectableControl();
	virtual ~SelectableControl();
	//static SelectableControl* get_cur_selectableControl();

	void push(Selectable* selectable);

	template <class selectClass>
	inline void push(std::vector<selectClass*>*selectables){
		for(unsigned i=0;i<selectables->size();i++){
			push(selectables->at(i));
		}
	}
	/*
	 * update all selectable object
	 */
	virtual void update();
	/*
	 *find current selected object
	 */
	Selectable* find_selected();

	Selectable* cur_selected;
	std::vector<Selectable*>selectables;
};
}
//#include "class/input/mouse/selectable/SelectableControl.cpp"
#endif /* SELECTABLECONTROL_H_ */
