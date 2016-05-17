/*
 * UnitController.h
 *
 *  Created on: 2016¦~5¤ë17¤é
 *      Author: LukeWu
 */

#ifndef SOURCE_CLASS_CONTROLLER_UNITCONTROLLER_H_
#define SOURCE_CLASS_CONTROLLER_UNITCONTROLLER_H_

#include <vector>
#include "class/controller/Controller.h"
#include "class/display/UI/unitUI/BuildingUI.h"
#include "class/game/ageOfCube/unit/Unit.h"

namespace AOC {

class UnitController: public Controller {
public:
	UnitController();
	virtual ~UnitController();
	void init_UI(std::string _path, UI::UIObject *_parent);
	void display_unit_UI();
	void hide_unit_UI();
	void select_unit(Unit *_unit);
	void deselect_unit();
protected:
	Unit *selected_unit;
	std::vector<Unit *>units;
	UI::BuildingUI *building_UI;
};

} /* namespace AOC */

#endif /* SOURCE_CLASS_CONTROLLER_UNITCONTROLLER_H_ */
