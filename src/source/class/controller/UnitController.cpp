#include "class/controller/UnitController.h"
#include "class/input/Input.h"
namespace AOC {

UnitController::UnitController() {
	building_UI = new UI::BuildingUI();
	selected_unit = 0;
	receiver=new Input::Receiver("UnitController");
	Input::Input::get_cur_object()->push_receiver(receiver);
	building_UI=new UI::BuildingUI();
	building_UI->Load_script("files/AgeOfCube/scenes/playTD/UI/unit_UI.txt");
}
UnitController::~UnitController() {
	delete building_UI;
	Input::Input::get_cur_object()->remove_receiver(receiver->get_name());
}
void UnitController::select_unit(Unit *_unit){
	selected_unit = _unit;
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
}
} /* namespace AOC */
