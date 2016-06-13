#include "class/game/ageOfCube/map/unit/UnitController.h"
#include "class/game/ageOfCube/map/minion/Minion.h"
#include "class/game/ageOfCube/map/building/Building.h"
#include "class/input/Input.h"
#include "class/tim/string/String.h"
#include "class/game/ageOfCube/map/Map.h"
#include "class/game/ageOfCube/player/Player.h"
#include "class/game/ageOfCube/player/PlayerController.h"
#include "class/tim/string/String.h"
#include <cstdio>
#include <iostream>
namespace AOC {

UnitController::UnitController() {
	minion_creator=new MinionCreator();
	building_UI = new UI::BuildingUI();
	selected_unit = 0;
	receiver=new Input::Receiver("UnitController");
	Input::Input::get_cur_object()->push_receiver(receiver);
	building_UI=new UI::BuildingUI();
	building_UI->Load_script("files/AgeOfCube/scenes/playTD/UI/unit_UI.txt");
	building_UI->init_buildingUI();
	building_UI->hide = true;
	register_cur();
}
UnitController::~UnitController() {
	delete minion_creator;
	for(unsigned i=0;i<units.size();i++){
		if(Minion* minion=dynamic_cast<Minion*>(units.at(i))){
			delete minion;
		}
	}
	delete building_UI;
	Input::Input::get_cur_object()->remove_receiver(receiver->get_name());

}
void UnitController::save(FILE * file){
	save_minion(file);
}
void UnitController::load(FILE * file){
	load_minion(file);
}
void UnitController::save_minion(FILE * file){
	std::vector<Minion*>minions;
	for(unsigned i=0;i<units.size();i++){
		if(Minion* minion=dynamic_cast<Minion*>(units.at(i))){
			minions.push_back(minion);
		}
	}
	fprintf(file,"%u\n",minions.size());
	for(unsigned i=0;i<minions.size();i++){
		fprintf(file,"%s\n",minions.at(i)->get_name().c_str());
		minions.at(i)->save(file);
	}
}
void UnitController::load_minion(FILE * file){
	unsigned size;
	char name[100];
	Minion* minion;
	fscanf(file,"%u\n",&size);
	for(unsigned i=0;i<size;i++){
		fscanf(file,"%s\n",name);
		minion=minion_creator->create(name);
		minion->load(file);
		minion->create_minion();
	}
}
Unit* UnitController::search_unit(std::string name,math::vec3<double>pos){
	Unit* unit=0;
	double min_dis=0,dis;
	for(unsigned i=0;i<units.size();i++){
		if(!units.at(i)->get_is_dead()&&units.at(i)->get_name()==name){
			if(unit){
				dis=(pos-units.at(i)->get_pos()).get_length();
				if(dis<min_dis){
					min_dis=dis;
					unit=units.at(i);
				}
			}else{
				unit=units.at(i);
				min_dis=(pos-units.at(i)->get_pos()).get_length();
			}

		}
	}
	return unit;
}
Unit* UnitController::search_unit(unsigned player,math::vec3<double>pos){
	Unit* unit=0;
	double min_dis=0,dis;
	for(unsigned i=0;i<units.size();i++){
		if(!units.at(i)->get_is_dead()&&units.at(i)->get_player()==player){
			if(unit){
				dis=(pos-units.at(i)->get_pos()).get_length();
				if(dis<min_dis){
					min_dis=dis;
					unit=units.at(i);
				}
			}else{
				unit=units.at(i);
				min_dis=(pos-units.at(i)->get_pos()).get_length();
			}

		}
	}
	return unit;
}
void UnitController::select_unit(Unit *unit){
	selected_unit = unit;
	Building *building = dynamic_cast<Building *>(unit);
	if(building){
		building_UI->set_selected_building(building);
	}
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
void UnitController::upgrade(std::string type){
	if(!selected_unit)return;

	Player *current_player = PlayerController::get_cur_object()->get_cur_player();
	if (selected_unit->get_player() != current_player->get_id()){
		std::cerr<<"can't upgrade other player's building"<<std::endl;
		return;
	}
	Building *selected_building = dynamic_cast<Building *>(selected_unit);
	if(!selected_building){
		std::cerr<<"can't non-building unit"<<std::endl;
		return;
	}
	ResourceModifier cost(type, -1);
	if(!current_player->modify_resource(cost)){
		std::cerr<<"resource not enough"<<std::endl;
		return;
	}
	selected_building->upgrade_building(type+"_upgrade");
}
void UnitController::handle_signal(){
	Input::Signal* sig;


	while((sig=receiver->get_signal())){
		std::vector<std::string> strs;
		Tim::String::split(sig->get_data(),"_",strs);

		if(sig->get_data()=="toggle_panel"){
			building_UI->hide^=1;
		}else if(strs.size()==2&&strs.at(1)=="upgrade"){
			upgrade(strs.at(0));
		}else{

		}
	}
}
void UnitController::update(){
	//std::cout<<"unit controller update"<<std::endl;
	building_UI->update();
	building_UI->update_UIObject();
	handle_signal();
	std::vector<Unit*>dead_units;
	for(unsigned i=0;i<units.size();i++){
		units.at(i)->update();
		if(units.at(i)->get_terminate()){
			dead_units.push_back(units.at(i));
		}
	}
	Unit* unit;
	for(unsigned i=0;i<dead_units.size();i++){
		//std::cout<<"UnitController::update() delete dead"<<std::endl;
		unit=dead_units.at(i);
		if(Minion*m=dynamic_cast<Minion*>(unit)){
			//std::cout<<"UnitController::update() delete minion"<<std::endl;
			delete m;
		}else if(Building* b=dynamic_cast<Building*>(unit)){
			math::vec3<int> pos=b->get_pos_int();
			Map::get_cur_object()->remove_cube(pos.x,pos.y,pos.z);
		}
	}
}
void UnitController::draw(Display::Draw* draw){
	building_UI->draw_UIObject(draw);
	for(unsigned i=0;i<units.size();i++){
		if(Minion* minion=dynamic_cast<Minion*>(units.at(i))){
			minion->draw();
		}
	}
	/*
	for(unsigned i=0;i<minions.size();i++){
		minions.at(i)->draw();
	}
	*/
}
} /* namespace AOC */
