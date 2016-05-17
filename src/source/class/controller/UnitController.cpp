/*
 * UnitController.cpp
 *
 *  Created on: 2016¦~5¤ë17¤é
 *      Author: LukeWu
 */

#include "class/controller/UnitController.h"

namespace AOC {

UnitController::UnitController() {
	// TODO Auto-generated constructor stub
	building_UI = new UI::BuildingUI();
}

UnitController::~UnitController() {
	// TODO Auto-generated destructor stub
}

void UnitController::init_UI(std::string _path, UI::UIObject *_parent){
	//unit_UI->Load_script("files/AgeOfCube/playTD/UI/unit_UI.txt");
	building_UI->Load_script(_path);
	//unit_UI->set_parent(_parent);
	_parent->push_child(building_UI); //push_child do set_parent automatically
}

void UnitController::select_unit(Unit *_unit){
	selected_unit = _unit;
	display_unit_UI();
}

void UnitController::deselect_unit(){
	selected_unit = 0;
	hide_unit_UI();
}

void UnitController::display_unit_UI(){
	building_UI->hide = false;
}

void UnitController::hide_unit_UI(){
	building_UI->hide = true;
}

} /* namespace AOC */
