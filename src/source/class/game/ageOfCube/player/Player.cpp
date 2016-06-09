#include "class/game/ageOfCube/player/Player.h"

namespace AOC {

Player::Player(int _id, PlayerType _type) {
	player_UI=new UI::PlayerUI();
	player_UI->Load_script("files/AgeOfCube/scenes/playTD/UI/player_UI.txt");
	type = _type;
	id = _id;
}
Player::~Player() {

}

void Player::draw(Display::Draw* draw){
	player_UI->draw_UIObject(draw);
}

void Player::update(){

}

} /* namespace AOC */
