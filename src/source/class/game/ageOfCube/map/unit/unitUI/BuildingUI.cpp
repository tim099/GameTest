#include "class/game/ageOfCube/map/unit/unitUI/BuildingUI.h"
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
	upgrade_str[0]=dynamic_cast<UIString*>(get_child("upgrade1_amount"));
	upgrade_str[1]=dynamic_cast<UIString*>(get_child("upgrade2_amount"));
	upgrade_str[2]=dynamic_cast<UIString*>(get_child("upgrade3_amount"));
	upgrade_str[3]=dynamic_cast<UIString*>(get_child("upgrade4_amount"));
}

void BuildingUI::set_selected_building(AOC::Building *_selected_building){
	selected_building = _selected_building;
	update();
}
void BuildingUI::clear_selected_building(){
	selected_building = 0;
}

void BuildingUI::update(){
	if(selected_building&&selected_building->get_is_dead()){
		selected_building=0;
	}
	if(!selected_building){
		return;
	}
	//std::cout<<"building UI update"<<std::endl;
	name_str->set_string(selected_building->get_name());
	hp_str->set_string(Tim::String::to_string(selected_building->get_hp())+"/"+
			Tim::String::to_string(selected_building->get_max_hp()));
	armor_str->set_string(Tim::String::to_string(selected_building->get_armor()));
	atk_str->set_string(Tim::String::to_string(selected_building->get_atk_ajusted()));
	upgrade_str[0]->set_string(Tim::String::to_string(selected_building->get_upgrade_amount("fire")));
	upgrade_str[1]->set_string(Tim::String::to_string(selected_building->get_upgrade_amount("water")));
	upgrade_str[2]->set_string(Tim::String::to_string(selected_building->get_upgrade_amount("earth")));
	upgrade_str[3]->set_string(Tim::String::to_string(selected_building->get_upgrade_amount("air")));
}

bool BuildingUI::check_script(){
	return true;
}
} /* namespace UI */
