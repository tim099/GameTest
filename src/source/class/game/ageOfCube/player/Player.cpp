#include "class/game/ageOfCube/player/Player.h"

namespace AOC {

Player::Player(int _id, PlayerType _type) {
	player_UI = 0;
	type = _type;
	id = _id;
	resources.push_back(Resource("cube","basic material for construction",100));
	resources.push_back(Resource("fire","advanced material for construction and upgrade",100));
	resources.push_back(Resource("water","advanced material for construction and upgrade",100));
	resources.push_back(Resource("earth","advanced material for construction and upgrade",100));
	resources.push_back(Resource("air","advanced material for construction and upgrade",100));
	resources.push_back(Resource("tech","technical material used for research",100));
}
Player::~Player() {
	delete player_UI;
}

void Player::init_UI(){
	player_UI=new UI::PlayerUI();
	player_UI->Load_script("files/AgeOfCube/scenes/playTD/UI/player_UI.txt");
	player_UI->init_playerUI();
}

void Player::draw(Display::Draw* draw){
	if(!player_UI)
		return;
	player_UI->draw_UIObject(draw);
}

void Player::update(){
	//std::cout<<"player update"<<std::endl;
	if(!player_UI)
		return;

	player_UI->set_resource_amount(0, resources.at(0).get_amount());
	player_UI->set_resource_amount(1, resources.at(1).get_amount());
	player_UI->set_resource_amount(2, resources.at(2).get_amount());
	player_UI->set_resource_amount(3, resources.at(3).get_amount());
	player_UI->set_resource_amount(4, resources.at(4).get_amount());
	player_UI->set_resource_amount(5, resources.at(5).get_amount());
}

bool Player::modify_resource(ResourceModifier modifier){
	for(unsigned int i=0; i<resources.size(); i++){
		if(resources.at(i).get_name() == modifier.get_name()){
			if(resources.at(i).get_amount() > modifier.get_amount()){
				 return resources.at(i).modifyAmount(modifier.get_amount());
			}
			break;
		}
	}
	return false;
}

} /* namespace AOC */
