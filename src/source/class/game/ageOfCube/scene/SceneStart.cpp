#include "class/game/ageOfCube/scene/SceneStart.h"
#include "class/tim/file/File.h"
#include "class/display/UI/string/UIString.h"
#include "class/tim/string/String.h"
#include "class/game/ageOfCube/scene/SceneEditMap.h"
#include "class/game/ageOfCube/scene/ScenePlayTD.h"

namespace AOC{
SceneStart::SceneStart() {
	UI=0;
	receiver=0;
	p_control=0;
	auto_p_control=0;
	map_folder_path="files/AgeOfCube/maps/";
	music_player = Audio::AudioPlayer("default_music/prepare_your_swords.wav");
	music_player.set_loop(true);
}
void SceneStart::scene_initialize(){

	resume();
	//std::vector<std::string> files=Tim::File::get_all_dirs("files/texture/");
	//for(unsigned i=0;i<files.size();i++)std::cout<<files.at(i)<<std::endl;
}
void SceneStart::scene_terminate(){
	//UI->Save_script("files/AgeOfCube/startScene/UI/startSceneUI.txt");
	if(UI){
		delete UI;
		UI=0;
	}
}
SceneStart::~SceneStart() {

}
void SceneStart::pause(){
	music_player.pause();

}
void SceneStart::resume(){
	std::cout<<"SceneStart::resume()"<<std::endl;
	music_player.play();
	draw->Enable3D=false;
	if(UI){
		delete UI;
		UI=0;
	}
	UI = new UI::UI("files/AgeOfCube/scenes/startScene/UI/startSceneUI.txt");
	p_control=(UI::PageControl*)UI->get_child("pageControl");
	auto_p_control=(UI::AutoPageControl*)UI->get_child("newGame_autoPageControl");
	//if(UI)delete UI;

	if(!p_control){
		std::cerr<<"SceneStart::scene_initialize ,can't find child page control"<<std::endl;
	}else{
		p_control->switch_page("startPage");
	}
	std::cout<<"SceneStart::resume() END"<<std::endl;
}
void SceneStart::handle_signal(Input::Signal* sig){
	std::cout<<"SceneStart got signal:"<<sig->get_data()<<std::endl;
	if(sig->get_data()=="CreateNewMap"){
		create_new_map();
	}else if(sig->get_data()=="CreateMap"){
		create_map();
	}else if(sig->get_data()=="edit_map"){
		load_map("edit");
	}else if(sig->get_data()=="delete_map"){
		delete_map();
	}else if(sig->get_data()=="play"){
		load_map("play");
	}
}
void SceneStart::load_map(std::string mode){
	std::string map_name=((UI::UIString*)UI->get_child("Selected_Map"))->get_string();
	if(map_name=="Null")return;
	Input::Signal *sig=new Input::Signal("push_scene","Game");

	if(mode == "edit"){
		sig->ex_data=new AOC::SceneEditMap(map_folder_path+map_name,
			glm::ivec3(1,1,1));
	}
	else if(mode == "play"){
		sig->ex_data=new AOC::ScenePlayTD(map_folder_path+map_name,
					glm::ivec3(1,1,1));
	}

	sig->sent();
}
void SceneStart::delete_map(){
	std::string map_name=((UI::UIString*)UI->get_child("Selected_Map"))->get_string();
	Tim::File::delete_file(map_folder_path+map_name);
	auto_p_control->update_pages();
}
void SceneStart::create_new_map(){
	UI::UIString *new_map_name=(UI::UIString*)UI->get_child("NewMapName");
	UI::UIString *new_map_size=(UI::UIString*)UI->get_child("NewMapSize");
	std::cout<<"new Map Name="<<new_map_name->get_string()<<std::endl;
	std::cout<<"new Map Size="<<new_map_size->get_string()<<std::endl;
	UI::PageControl* createNewMap_pc=(UI::PageControl*)UI->get_child("createNewMap_pageControl");
	createNewMap_pc->switch_page("newMap");
	UI::UIString *map_name=(UI::UIString*)UI->get_child("MapName");
	UI::UIString *map_size=(UI::UIString*)UI->get_child("MapSize");
	map_name->set_string(new_map_name->get_string());
	map_size->set_string(new_map_size->get_string());
}
void SceneStart::create_map(){
	UI::UIString *map_name=(UI::UIString*)UI->get_child("MapName");
	UI::UIString *map_size_str=(UI::UIString*)UI->get_child("MapSize");
	std::vector<std::string> size;
	Tim::String::split(map_size_str->get_string(),"*",size);
	std::cout<<"Map Name="<<map_name->get_string()<<std::endl;
	unsigned map_size[3];
	std::cout<<"map size=";
	if(size.size()!=3){
		std::cerr<<"SceneStart::create_map() fail!! Invalid Map Size:"
				<<map_size_str->get_string()<<std::endl;
		std::cerr<<"Please Enter Map Size"<<std::endl;
		return ;
	}
	for(int i=0;i<3;i++){
		map_size[i]=Tim::String::str_to_int(size.at(i).c_str());
		//sscanf(size.at(i).c_str(),"%u",&map_size[i]);
		std::cout<<map_size[i]<<",";
	}std::cout<<std::endl;
	Input::Signal *sig=new Input::Signal("push_scene","Game");
	sig->ex_data=new AOC::SceneEditMap(map_folder_path+std::string(map_name->get_string()),
			glm::ivec3(map_size[0],map_size[1],map_size[2]));
	//sig->ex_data=new SceneStart();
	sig->sent();

}
void SceneStart::handle_input(){
	///*
	if(input->keyboard->get('E')){
		if(UI->check_mode(UI::Mode::EDIT)){
			UI->Disable_Mode(UI::Mode::EDIT);
		}else{
			UI->Enable_Mode(UI::Mode::EDIT);
		}
	}else if(input->keyboard->get('S')){
		UI->Save_script("files/AgeOfCube/startScene/UI/startSceneUI.txt");
	}else if(input->keyboard->get('L')){
		//delete UI;
		UI = new UI::UI("files/AgeOfCube/startScene/UI/startSceneUI.txt");
	}
	//*/
}
void SceneStart::scene_update(){
	handle_input();

	UI->update_UIObject();
}
void SceneStart::scene_draw(){
	UI->draw_UIObject(draw);
}
}
