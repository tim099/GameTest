/*
 * BuildingUI.h
 *
 *  Created on: 2016¦~5¤ë18¤é
 *      Author: LukeWu
 */

#ifndef SOURCE_CLASS_DISPLAY_UI_UNITUI_BUILDINGUI_H_
#define SOURCE_CLASS_DISPLAY_UI_UNITUI_BUILDINGUI_H_

#include <string>
#include "class/display/UI/UI.h"

namespace AOC{
	class Building;
}

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
	bool check_script();
protected:

};

} /* namespace UI */

#endif /* SOURCE_CLASS_DISPLAY_UI_UNITUI_BUILDINGUI_H_ */
