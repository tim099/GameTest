#include "class/game/ageOfCube/player/Player.h"

namespace AOC {

Player::Player(int _id, PlayerType _type) {
	player_UI = 0;
	score = 0;
	type = _type;
	id = _id;
	resources.push("cube", new Resource("cube","basic material for construction",100));
	resources.push("fire",new Resource("fire","advanced material for construction and upgrade",100));
	resources.push("water",new Resource("water","advanced material for construction and upgrade",100));
	resources.push("earth",new Resource("earth","advanced material for construction and upgrade",100));
	resources.push("air",new Resource("air","advanced material for construction and upgrade",100));
	resources.push("tech",new Resource("tech","technical material used for research",100));
}
Player::~Player() {
	if(player_UI)delete player_UI;
}
void Player::save(FILE *file){

}
void Player::load(FILE *file){

}
void Player::set_score(int _score){
	//std::cout<<"Player::set_score:"<<_score<<std::endl;
	score=_score;
	if(player_UI){
		player_UI->set_score(score);
	}

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

	player_UI->set_resource_amount(0, resources.get("cube")->get_amount());
	player_UI->set_resource_amount(1, resources.get("fire")->get_amount());
	player_UI->set_resource_amount(2, resources.get("water")->get_amount());
	player_UI->set_resource_amount(3, resources.get("earth")->get_amount());
	player_UI->set_resource_amount(4, resources.get("air")->get_amount());
	player_UI->set_resource_amount(5, resources.get("tech")->get_amount());
	player_UI->set_score(score);
}

bool Player::modify_resource(ResourceModifier modifier){
	if(Resource *modified_resource = resources.get(modifier.get_name())){
		if(modified_resource->get_amount() > modifier.get_amount()){
			 return modified_resource->modifyAmount(modifier.get_amount());
		}
	}
	return false;
}

bool Player::modify_resource(std::string resource_name, int requested_amount){
	if(Resource *modified_resource = resources.get(resource_name)){
		if(modified_resource->get_amount() >= requested_amount){
			 return modified_resource->modifyAmount(requested_amount);
		}
	}
	return false;
}

} /* namespace AOC */
