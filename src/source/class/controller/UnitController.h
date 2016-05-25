#ifndef SOURCE_CLASS_CONTROLLER_UNITCONTROLLER_H_
#define SOURCE_CLASS_CONTROLLER_UNITCONTROLLER_H_

#include <vector>
#include "class/controller/Controller.h"
#include "class/display/UI/unitUI/BuildingUI.h"
#include "class/game/ageOfCube/unit/Unit.h"
#include "class/tim/globalObject/GlobalObject.h"
#include "class/input/signal/Receiver.h"
#include "class/display/UI/string/UIString.h"
namespace Display{
class Draw;
}
namespace AOC {

class UnitController: public Controller ,public Tim::GlobalObject<UnitController>{
public:
	UnitController();
	virtual ~UnitController();
	void display_unit_UI();
	void hide_unit_UI();
	void select_unit(Unit *_unit);
	void deselect_unit();
	virtual void update();
	void draw(Display::Draw* draw);
protected:
	void handle_signal();
	Unit *selected_unit;
	std::vector<Unit *>units;
	UI::BuildingUI *building_UI;
	UI::UIString *name_str;
	UI::UIString *atk_str;
	UI::UIString *armor_str;
	UI::UIString *hp_str;
	Input::Receiver* receiver;
};

} /* namespace AOC */

#endif /* SOURCE_CLASS_CONTROLLER_UNITCONTROLLER_H_ */
