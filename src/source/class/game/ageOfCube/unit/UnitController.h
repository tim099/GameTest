#ifndef SOURCE_CLASS_CONTROLLER_UNITCONTROLLER_H_
#define SOURCE_CLASS_CONTROLLER_UNITCONTROLLER_H_

#include <vector>
#include "class/controller/Controller.h"
#include "class/display/UI/unitUI/BuildingUI.h"
#include "class/game/ageOfCube/unit/Unit.h"
#include "class/tim/globalObject/GlobalObject.h"
#include "class/input/signal/Receiver.h"
#include "class/display/UI/string/UIString.h"
#include "class/game/ageOfCube/map/minion/MinionCreator.h"
#include "class/tim/pointer/SmartPointer.h"
namespace Display{
class Draw;
}
namespace AOC {
class Minion;
class UnitController: public Controller ,public Tim::GlobalObject<UnitController>{
public:
	UnitController();
	virtual ~UnitController();
	virtual void update();

	void display_unit_UI();
	void hide_unit_UI();
	void select_unit(Unit *_unit);
	void deselect_unit();
	void draw(Display::Draw* draw);
	void push(Unit* unit){
		units.push_back(unit);
	}
	void remove(Unit* unit){
		for(unsigned i=0;i<units.size();i++){
			if(units.at(i)==unit){
				units.at(i)=units.back();
				units.pop_back();
			}
		}
	}
	/*
	void push_minion(Minion* unit){
		minions.push_back(unit);
	}
	void remove_minion(Minion* minion){
		for(unsigned i=0;i<minions.size();i++){
			if(minions.at(i)==minion){
				minions.at(i)=minions.back();
				minions.pop_back();
			}
		}
	}
	*/
	void save(FILE *file);
	void load(FILE *file);
	MinionCreator* minion_creator;
protected:
	void handle_signal();
	void save_minion(FILE *file);
	void load_minion(FILE *file);
	Unit *selected_unit;
	std::vector<Unit*>units;
	//std::vector<Minion*>minions;
	UI::BuildingUI *building_UI;
	UI::UIString *name_str;
	UI::UIString *atk_str;
	UI::UIString *armor_str;
	UI::UIString *hp_str;
	Input::Receiver* receiver;

};

} /* namespace AOC */

#endif /* SOURCE_CLASS_CONTROLLER_UNITCONTROLLER_H_ */
