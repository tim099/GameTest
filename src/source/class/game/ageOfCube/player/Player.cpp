#include "class/game/ageOfCube/player/Player.h"

namespace AOC {

Player::Player(int _id, PlayerType _type) {
	player_UI=new UI::PlayerUI();
	player_UI->Load_script("files/AgeOfCube/scenes/playTD/UI/player_UI.txt");
	type = _type;
	id = _id;
	resources.push_back(Resource("cube","basic material for construction",100));
	resources.push_back(Resource("fire","advanced material for construction and upgrade",100));
	resources.push_back(Resource("water","advanced material for construction and upgrade",100));
	resources.push_back(Resource("earth","advanced material for construction and upgrade",100));
	resources.push_back(Resource("water","advanced material for construction and upgrade",100));
	resources.push_back(Resource("tech","technical material used for research",100));
}
Player::~Player() {

}

void Player::draw(Display::Draw* draw){
	player_UI->draw_UIObject(draw);
}

void Player::update(){

}

bool Player::modify_resource(ResourceModifier modifier){
	for(unsigned int i=0; i<resources.size(); i++){
		if(resources.at(i).get_name() == modifier.get_name()){
			if(resources.at(i).get_amount() > modifier.get_amount()){
				resources.at(i).modifyAmount(modifier.get_amount());
			}
			break;
		}
	}
	return false;
}

} /* namespace AOC */
