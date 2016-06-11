#include "class/display/UI/unitUI/BuildingUI.h"
#include "class/tim/string/String.h"
#include <iostream>

namespace UI {

BuildingUI::BuildingUI() {
	name_str=0;
	atk_str=0;
	armor_str=0;
	hp_str=0;
	selected_building = 0;
}
BuildingUI::~BuildingUI() {

}
void BuildingUI::init_buildingUI(){
	name_str=dynamic_cast<UIString*>(get_child("name"));
	atk_str=dynamic_cast<UIString*>(get_child("atk"));
	armor_str=dynamic_cast<UIString*>(get_child("armor"));
	hp_str=dynamic_cast<UIString*>(get_child("hp"));
}

void BuildingUI::set_selected_building(AOC::Building *_selected_building){
	selected_building = _selected_building;
	update();
}
void BuildingUI::clear_selected_building(){

}

void BuildingUI::update(){
	if(!selected_building)return;
	std::cout<<"building UI update"<<std::endl;
	name_str->set_string(selected_building->get_name());
	hp_str->set_string(Tim::String::to_string(selected_building->get_hp())+"/"+
			Tim::String::to_string(selected_building->get_max_hp()));
	armor_str->set_string(Tim::String::to_string(selected_building->get_armor()));
	atk_str->set_string(Tim::String::to_string(selected_building->get_atk()));
}

bool BuildingUI::check_script(){
	return true;
}
} /* namespace UI */
