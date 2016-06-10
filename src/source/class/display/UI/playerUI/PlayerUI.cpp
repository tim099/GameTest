/*
 * PlayerUI.cpp
 *
 *  Created on: 2016�~6��9��
 *      Author: LukeWu
 */

#include <iostream>
#include "class/display/UI/playerUI/PlayerUI.h"
#include "class/tim/string/String.h"

namespace UI {

PlayerUI::PlayerUI() {
	inited = false;
}

PlayerUI::~PlayerUI() {
	// TODO Auto-generated destructor stub
}

void PlayerUI::init_playerUI(){
	resource_amount_strings[0] = dynamic_cast<UIString *>(get_child("resource1_amount"));
	resource_amount_strings[1] = dynamic_cast<UIString *>(get_child("resource2_amount"));
	resource_amount_strings[2] = dynamic_cast<UIString *>(get_child("resource3_amount"));
	resource_amount_strings[3] = dynamic_cast<UIString *>(get_child("resource4_amount"));
	resource_amount_strings[4] = dynamic_cast<UIString *>(get_child("resource5_amount"));
	resource_amount_strings[5] = dynamic_cast<UIString *>(get_child("resource6_amount"));
	for(int i=0;i<6; i++){
		if(!resource_amount_strings[i]){
			std::cout<<"resource string "<<i<<" cast fail"<<std::endl;
		}
	}

	inited = true;
}

bool PlayerUI::check_script(){
	return true;
}

void PlayerUI::set_resource_amount(unsigned int resource_string_id, int value){
	//std::cout<<"set_resource "<<resource_string_id<<" amount "<<value<<std::endl;
	if(!inited){
		return;
	}
	if(resource_string_id > 5){
		std::cerr<<"resource string id out of bound"<<std::endl;
		return;
	}
	resource_amount_strings[resource_string_id]->set_string(Tim::String::to_string(value));
}

} /* namespace AOC */
