#include "class/game/ageOfCube/unit/UnitController.h"
#include "class/game/ageOfCube/map/minion/Minion.h"
#include "class/input/Input.h"
#include "class/tim/string/String.h"
#include <cstdio>
namespace AOC {

UnitController::UnitController() {
	minion_creator=new MinionCreator();
	building_UI = new UI::BuildingUI();
	selected_unit = 0;
	receiver=new Input::Receiver("UnitController");
	Input::Input::get_cur_object()->push_receiver(receiver);
	building_UI=new UI::BuildingUI();
	building_UI->Load_script("files/AgeOfCube/scenes/playTD/UI/unit_UI.txt");
	name_str=dynamic_cast<UI::UIString*>(building_UI->get_child("name"));
	atk_str=dynamic_cast<UI::UIString*>(building_UI->get_child("atk"));
	armor_str=dynamic_cast<UI::UIString*>(building_UI->get_child("armor"));
	hp_str=dynamic_cast<UI::UIString*>(building_UI->get_child("hp"));
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
		minion->recruit();
	}
}
Unit* UnitController::search_unit(std::string name,math::vec3<double>pos){
	Unit* unit=0;
	double min_dis=0,dis;
	for(unsigned i=0;i<units.size();i++){
		if(units.at(i)->get_name()==name){
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
Unit* UnitController::search_unit(int player,math::vec3<double>pos){
	Unit* unit=0;
	double min_dis=0,dis;
	for(unsigned i=0;i<units.size();i++){
		if(units.at(i)->get_player()==player){
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
	name_str->set_string(unit->get_name());
	hp_str->set_string(Tim::String::to_string(unit->get_hp())+"/"+
			Tim::String::to_string(unit->get_max_hp()));
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
void UnitController::handle_signal(){
	Input::Signal* sig;
	while((sig=receiver->get_signal())){
		if(sig->get_data()=="toggle_panel"){
			building_UI->hide^=1;
		}else{

		}
	}
}
void UnitController::update(){
	building_UI->update_UIObject();
	handle_signal();
	for(unsigned i=0;i<units.size();i++){
		units.at(i)->unit_update();
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
