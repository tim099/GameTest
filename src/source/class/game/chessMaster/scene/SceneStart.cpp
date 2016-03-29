#include "class/game/chessMaster/scene/SceneStart.h"
#include "class/game/chessMaster/common.h"

namespace CM {
namespace scene{
SceneStart::SceneStart() {
	UI=0;
	local_path=std::string("scene/start/");
	chess_board=0;
}
SceneStart::~SceneStart() {

}
void SceneStart::scene_initialize() {
	draw->Enable3D=false;
	chess_board=new ChessBoard();
	UI = new UI::UI(CM::folder_path+local_path+"UI/startUI.txt");
	UI->Enable_Mode(UI::Mode::EDIT);
}
void SceneStart::scene_terminate() {
	if(UI){
		delete UI;
		UI=0;
	}
}
void SceneStart::pause(){

}
void SceneStart::resume(){

}
void SceneStart::handle_signal(Signal *sig){
	std::cout<<sig->get_data()<<std::endl;
}
void SceneStart::scene_update(){
	UI->update_UIObject();

}
void SceneStart::scene_draw(){
	UI->draw_UIObject(draw);
}



}
} /* namespace CM */
