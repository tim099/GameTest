#ifndef SOURCE_CLASS_DISPLAY_UI_UNITUI_BUILDINGUI_H_
#define SOURCE_CLASS_DISPLAY_UI_UNITUI_BUILDINGUI_H_

#include <string>
#include "class/display/UI/UI.h"
#include "class/display/UI/string/UIString.h"
#include "class/game/ageOfCube/map/building/Building.h"

namespace UI {

class BuildingUI : public UI{
public:
	BuildingUI();
	virtual ~BuildingUI();
	virtual UIObject* create_UIObject(){
		return new BuildingUI();
	}
	virtual std::string get_type()const{
		return "BuildingUI";
	}
	void set_selected_building(AOC::Building *);
	void clear_selected_building();
	void init_buildingUI();
	void update();
	bool check_script();
protected:
	UIString *name_str;
	UIString *atk_str;
	UIString *armor_str;
	UIString *hp_str;
	UIString *upgrade_str[4];
	AOC::Building *selected_building;
};

} /* namespace UI */

#endif /* SOURCE_CLASS_DISPLAY_UI_UNITUI_BUILDINGUI_H_ */
