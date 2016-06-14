#include "class/game/ageOfCube/player/Player.h"
#include <cstdio>
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
	fprintf(file,"%d %d %d %d %d %d\n",resources.get("cube")->get_amount(),
						   resources.get("fire")->get_amount(),
						   resources.get("water")->get_amount(),
						   resources.get("earth")->get_amount(),
						   resources.get("air")->get_amount(),
						   resources.get("tech")->get_amount());
	fprintf(file,"%d\n",score);
}
void Player::load(FILE *file){
	int cube,fire,water,earth,air,tech;
	fscanf(file,"%d %d %d %d %d %d\n",&cube,&fire,&water,&earth,&air,&tech);
	resources.get("cube")->set_amount(cube);
	resources.get("fire")->set_amount(fire);
	resources.get("water")->set_amount(water);
	resources.get("earth")->set_amount(earth);
	resources.get("air")->set_amount(air);
	resources.get("tech")->set_amount(tech);
	fscanf(file,"%d\n",&score);
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
		if(requested_amount>0||modified_resource->get_amount()+requested_amount >= 0){
			 return modified_resource->modifyAmount(requested_amount);
		}
	}
	return false;
}

} /* namespace AOC */
