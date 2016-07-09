#include "class/game/chessMaster/scene/SceneEdit.h"

#include "class/game/chessMaster/chessboard/chineseChess/ChineseChess.h"
#include "class/game/chessMaster/chessboard/renju/Renju.h"
#include "class/game/chessMaster/common.h"
#include "class/display/light/LightControl.h"
#include "class/display/draw/drawObject/AllDrawObjects.h"
#include "class/game/chessMaster/AI/AI.h"
#include "class/tim/math/Position.h"
#include "class/tim/string/String.h"
#include "class/display/draw/drawObject/drawData/drawDateEX/SkyMap.h"
#include "class/audio/AudioController.h"
#include <stdlib.h>
#include <time.h>
namespace CM {
namespace scene{
SceneEdit::SceneEdit() {
	UI = 0;
	local_path = std::string("scene/edit/");
	chess_board = 0;
	camera = 0;
	lightControl = 0;
	destruct_mode=false;
	type=1;
	chess_type=0;
	edit_chess=false;
	back_music=0;
}
SceneEdit::~SceneEdit() {

}
void SceneEdit::init_board(){
	type=1;
	chess_type=0;
}
void SceneEdit::scene_initialize() {
	chess_board=new Renju();
	//chess_board=new ChessBoard();
	//chess_board->load_script(CM::folder_path+"game/chess/chessBoard/boardscript.txt");

	glm::vec3 pos2=glm::vec3(0.5*chess_board->cube_size*chess_board->size.x,10,
			chess_board->cube_size*chess_board->size.z+2);

	camera=new Display::Camera(pos2,
			pos2+glm::vec3(0,-7,-0.5f*chess_board->size.z),
			glm::vec3(0, 1, 0), 60.0, 0.1f,
			10000.0f);
	draw->set_camera(camera);

	lightControl = new Display::LightControl(120);
	lightControl->shadow_dis=3.0f;
	lightControl->push_light(
			new Display::ParallelLight(glm::vec3(1.0, -1.2, 0.2),
					glm::vec3(0.6, 0.6, 0.6), false));
	lightControl->push_light(
			new Display::ParallelLight(glm::vec3(-0.5, -0.5, 2.1),
					glm::vec3(0.8, 0.8, 0.8), false));
	lightControl->push_light(
			new Display::ParallelLight(glm::vec3(-0.2, -1.2, -1.1),
					glm::vec3(1.2, 1.2, 1.2), true));
	lightControl->push_light(
			new Display::ParallelLight(glm::vec3(0.5, -0.4, -0.7),
					glm::vec3(0.4, 0.4, 0.4), false));


	draw->set_lightControl(lightControl);
	UI = new UI::UI(CM::folder_path+local_path+"UI/UI.txt");

	back_music=new Audio::AudioPlayer();
	back_music->set_source("default_music/prepare_your_swords.wav");
	back_music->set_volume(0.2);
	back_music->set_loop(true);

	resume();
	std::cout<<"SceneEdit::scene_initialize() 2"<<std::endl;
}
void SceneEdit::loading(){

}
void SceneEdit::scene_terminate() {
	if(back_music)delete back_music;
	delete chess_board;
	delete camera;
	delete lightControl;
	delete UI;
}
void SceneEdit::pause(){
	back_music->pause();
}
void SceneEdit::resume(){
	back_music->play();
	draw->Enable3D = true;
}
void SceneEdit::handle_signal(Input::Signal *sig){
	//std::cerr<<sig->get_data()<<std::endl;
	//std::cerr<<"SceneEdit::handle_signal 1"<<std::endl;
	if(sig->get_data()=="edit_chess"){
		edit_chess=true;
	}else if(sig->get_data()=="edit_board"){
		edit_chess=false;
	}else if(sig->get_data()=="edit_chess"){
		delete chess_board;
		chess_board=new ChessBoard(9,3,10);
		chess_board->load_script(CM::folder_path+"game/chess/chessBoard/boardscript.txt");
		init_board();
	}else if(sig->get_data()=="edit_chineseChess"){
		delete chess_board;
		chess_board=new ChineseChess();
		//chess_board->load_script(CM::folder_path+"game/chineseChess/chessBoard/boardscript.txt");
		init_board();
	}else if(sig->get_data()=="edit_renju"){
		delete chess_board;
		chess_board=new Renju();
		init_board();
	}else if(sig->get_data()=="load_board"){
		chess_board->load_board(chess_board->dir_path+"chessBoard/board.txt");
	}else if(sig->get_data()=="save_board"){
		chess_board->save_board(chess_board->dir_path+"chessBoard/board.txt");
	}

	//
	//std::cerr<<"SceneEdit::handle_signal 2"<<std::endl;
	//std::cout<<sig->get_data()<<std::endl;
}
void SceneEdit::camera_control(){
	if(input->keyboard->pressed('R')){
		camera->v.y += 0.01f* sqrt(camera->look_dis() + 0.001);
	}
	if(input->keyboard->pressed('F')){
		camera->v.y -= 0.01f* sqrt(camera->look_dis() + 0.001);
	}
	if(input->keyboard->get('V')){
		destruct_mode^=1;
	}
	if (input->mouse->mid_pressed()||input->keyboard->pressed('Z')) {
		//std::cout<<"move"<<(int)(mouse->pos.x)<<","<<(int)mouse->prev_pos.x<<std::endl;
		camera->rotate(glm::vec3(0, 1, 0), -0.15 * input->mouse->pos_delta().x);
		camera->rotate(camera->yaw_vec(), 0.15 * input->mouse->pos_delta().y);
	}
	//camera->rotate(glm::vec3(0, 1, 0), 1.0f);
	if(input->mouse->screen_pos.y>0.95){
		camera->v += (float) (-0.007f * sqrt(camera->look_dis() + 0.001))
				* camera->look_vec_xz();
	}
	if(input->mouse->screen_pos.y<-0.95){
		camera->v += (float) (0.007f * sqrt(camera->look_dis() + 0.001))
				* camera->look_vec_xz();
	}
	if(input->mouse->screen_pos.x>0.95){
		camera->v += (float) (-0.007f * sqrt(camera->look_dis() + 0.001))
		* glm::cross(camera->look_vec_xz(), glm::vec3(0, 1, 0));
	}
	if(input->mouse->screen_pos.x<-0.95){
		camera->v += (float) (0.007f * sqrt(camera->look_dis() + 0.001))
		* glm::cross(camera->look_vec_xz(), glm::vec3(0, 1, 0));
	}
	if (input->mouse->right_pressed()) {
		camera->v += (float) (0.0005f * sqrt(camera->look_dis() + 0.001)
				* input->mouse->pos_delta().y) * camera->look_vec_xz();
		camera->v += (float) (-0.0005f * sqrt(camera->look_dis() + 0.001)
				* input->mouse->pos_delta().x)
				* glm::cross(camera->look_vec_xz(), glm::vec3(0, 1, 0));
	}
	if (input->mouse->scroll) {
		camera->dis_alter_v += sqrt(camera->look_dis() + 0.1)
				* (0.05 * input->mouse->scroll);
	}
	if(camera->look_at.x>0.95*chess_board->cube_size*chess_board->size.x){
		if(camera->v.x>0.0f){
			camera->v.x*=-0.9f;
		}
	}else if(camera->look_at.x<0.05*chess_board->cube_size*chess_board->size.x){
		if(camera->v.x<0.0f){
			camera->v.x*=-0.9f;
		}
	}
	if(camera->look_at.z>0.95*chess_board->cube_size*chess_board->size.z){
		if(camera->v.z>0.0f){
			camera->v.z*=-0.9f;
		}
	}else if(camera->look_at.z<0.05*chess_board->cube_size*chess_board->size.z){
		if(camera->v.z<0.0f){
			camera->v.z*=-0.9f;
		}
	}
}
void SceneEdit::handle_input(){

	if (input->mouse->left_clicked()) {
		if(!destruct_mode){
			if(edit_chess){
					chess_board->set_type(chess_board->selected_on.x,
							chess_board->selected_on.z,chess_type);
			}else{
					chess_board->set_type(chess_board->selected_on.x,
										chess_board->selected_on.y,
										chess_board->selected_on.z,type);
			}
		}else{
			if(edit_chess){
				chess_board->set_type(chess_board->selected_on.x,
						chess_board->selected_on.z,-chess_type);
			}else{
				chess_board->set_type(chess_board->selected_cube.x,
									chess_board->selected_cube.y,
									chess_board->selected_cube.z,0);
			}
		}

	}

	if(input->keyboard->get('Q')){
		edit_chess^=1;
	}
	/*
	if(input->keyboard->get('S')){
		//chess_board->save_board(CM::folder_path+"game/chess/chessBoard/board.txt");
		chess_board->save_board(chess_board->dir_path+"chessBoard/board.txt");
	}
	if(input->keyboard->get('L')){
		//chess_board->load_board(CM::folder_path+"game/chess/chessBoard/board.txt");
		chess_board->load_board(chess_board->dir_path+"chessBoard/board.txt");
	}
	*/
	if(input->keyboard->get(Input::KeyCode::Plus)){
		if(edit_chess){
			if(chess_type<(int)chess_board->pieces.size()){
				chess_type++;
			}
		}else{
			if(type<chess_board->cube_type_num)type++;
		}

	}
	if(input->keyboard->get(Input::KeyCode::Minus)){
		if(edit_chess){
			if(chess_type>0)chess_type--;
		}else{
			if(type>0)type--;
		}
	}
	camera_control();
}
void SceneEdit::scene_update(){
	handle_input();
	camera->update();

	UI->update_UIObject();
	chess_board->find_select_cube();
	chess_board->winner=chess_board->check_winner(chess_board->chess_board);
}
void SceneEdit::scene_draw(){
	UI->draw_UIObject(draw);

	Display::DrawObject* galaxy=Display::AllDrawObjects::get_cur_object()->get("default/galaxy");
	Display::DrawDataObj* data=new Display::DrawDataObj(&back_ground_pos,false,false);
	data->push_ex_data(new Display::drawDataEX::SkyMap());
	galaxy->push_temp_drawdata(data);


	draw->push(new Display::RenderString(Tim::String::to_string(chess_board->selected_piece.x)+","+
	Tim::String::to_string(chess_board->selected_piece.y),0.02,math::vec2<float>(0.6,0.95)));

	if(edit_chess){
		static math::Position pos=math::Position(glm::vec3(), glm::vec3());
		pos.set_pos(glm::vec3((chess_board->selected_on.x+0.5f)*chess_board->cube_size,
				(chess_board->selected_on.y+0.5f)*chess_board->cube_size,
				(chess_board->selected_on.z+0.5f)*chess_board->cube_size));
		if(chess_type>0)chess_board->pieces.at(chess_type-1)->draw(&pos,!destruct_mode);
		draw->push(new Display::RenderString("Edit Chess",0.02,math::vec2<float>(0.7,0.95)));
	}else{
		draw->push(new Display::RenderString("Edit Board",0.02,math::vec2<float>(0.7,0.95)));
	}



	chess_board->draw();
	Display::CubeLight* cl=new Display::CubeLight();
	cl->size=1.01f*chess_board->cube_size;

	if(destruct_mode){
		cl->color=glm::vec3(1,0,0);
		cl->pos=glm::vec3((chess_board->selected_cube.x+0.5f)*chess_board->cube_size,
						  (chess_board->selected_cube.y+0.5f)*chess_board->cube_size,
						  (chess_board->selected_cube.z+0.5f)*chess_board->cube_size);
	}else{
		cl->color=glm::vec3(0,1,0);
		cl->pos=glm::vec3((chess_board->selected_on.x+0.5f)*chess_board->cube_size,
				  (chess_board->selected_on.y+0.5f)*chess_board->cube_size,
				  (chess_board->selected_on.z+0.5f)*chess_board->cube_size);
	}
	lightControl->push_temp_light(cl);
}



}
} /* namespace CM */
