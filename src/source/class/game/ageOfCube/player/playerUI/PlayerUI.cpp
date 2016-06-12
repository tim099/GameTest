/*
 * PlayerUI.cpp
 *
 *  Created on: 2016¦~6¤ë9¤é
 *      Author: LukeWu
 */

#include <iostream>
#include "class/game/ageOfCube/player/playerUI/PlayerUI.h"
#include "class/tim/string/String.h"

namespace UI {

PlayerUI::PlayerUI() {
	inited = false;
	score_string = 0;
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

	score_string = dynamic_cast<UIString *>(get_child("player_score"));

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

void PlayerUI::set_score(int score){
	//std::cout<<"set_resource "<<resource_string_id<<" amount "<<value<<std::endl;
	if(!inited){
		return;
	}
	score_string->set_string(Tim::String::to_string(score));
}

} /* namespace AOC */
