#include "class/game/chessMaster/scene/SceneStart.h"
#include "class/game/chessMaster/common.h"
#include "class/display/light/LightControl.h"
#include "class/display/draw/drawObject/AllDrawObjects.h"
#include "class/game/chessMaster/AI/AI.h"
#include "class/game/chessMaster/AI/TaskAI.h"
#include "class/tim/math/Position.h"
#include "class/tim/string/String.h"
#include "class/game/chessMaster/chessboard/chess/ChineseChess.h"
#include <stdlib.h>
#include <time.h>
namespace CM {
namespace scene{
SceneStart::SceneStart() {
	UI = 0;
	local_path = std::string("scene/start/");
	chess_board = 0;
	camera = 0;
	p1camera = 0,p2camera = 0;;
	lightControl = 0;
	destruct_mode=false;
	type=1;
	chess_type=0;
	selected=false;
	prev_sx=0;prev_sy=0;
	difficulty=3;
	edit_mode=false;
	edit_chess=false;
	AI_mode=0;
	ai=0;
}
SceneStart::~SceneStart() {

}
void SceneStart::scene_initialize() {
	std::cout<<"SceneStart::scene_initialize() 1"<<std::endl;
	//draw->Enable3D=false;
	//int sizex=9,sizey=3,sizez=10;
	//chess_board=new ChessBoard(9,3,10);
	chess_board=new ChineseChess();
	//chess_board->load_board(CM::folder_path+"game/chineseChess/chessBoard/board.txt");
	//chess_board->load_script(CM::folder_path+"game/chineseChess/chessBoard/boardscript.txt");
	//chess_board->load_script(CM::folder_path+"game/chess/chessBoard/boardscript.txt");

	ai=new CM::AI();
	glm::vec3 pos=glm::vec3(0.5*chess_board->cube_size*chess_board->size.x,6,-3);
	p1camera = new Display::Camera(pos,
			pos+glm::vec3(0,-4,0.5f*chess_board->size.z),
			glm::vec3(0, 1, 0), 60.0, 0.1f,
			10000.0f);
	glm::vec3 pos2=glm::vec3(0.5*chess_board->cube_size*chess_board->size.x,6,10);
	p2camera = new Display::Camera(pos2,
			pos2+glm::vec3(0,-4,-0.5f*chess_board->size.z),
			glm::vec3(0, 1, 0), 60.0, 0.1f,
			10000.0f);
	camera=p2camera;
	draw->set_camera(camera);

	lightControl = new Display::LightControl(120);
	lightControl->shadow_dis=3.0f;
	lightControl->push_light(
			new Display::ParallelLight(glm::vec3(1.0, -1.2, 0.2),
					glm::vec3(0.6, 0.6, 0.6), false));
	lightControl->push_light(
			new Display::ParallelLight(glm::vec3(-0.5, -0.5, 2.1),
					glm::vec3(1.1, 1.1, 1.1), true));
	lightControl->push_light(
			new Display::ParallelLight(glm::vec3(-0.2, -1.2, -1.1),
					glm::vec3(0.9, 0.9, 0.9), true));
	lightControl->push_light(
			new Display::ParallelLight(glm::vec3(0.5, -0.4, -0.7),
					glm::vec3(0.4, 0.4, 0.4), false));


	draw->set_lightControl(lightControl);
	UI = new UI::UI(CM::folder_path+local_path+"UI/startUI.txt");
	resume();
	//UI->Enable_Mode(UI::Mode::EDIT);
	std::cout<<"SceneStart::scene_initialize() 2"<<std::endl;
}
void SceneStart::loading(){

}
void SceneStart::scene_terminate() {
	delete ai;
	delete chess_board;
	delete p1camera;
	delete p2camera;
	delete lightControl;
	delete UI;
}
void SceneStart::pause(){

}
void SceneStart::resume(){
	draw->Enable3D = true;
}
void SceneStart::handle_signal(Input::Signal *sig){
	//std::cerr<<"SceneStart::handle_signal 1"<<std::endl;
	if(sig->get_data()=="hard"){
		difficulty=6;
	}else if(sig->get_data()=="normal_plus"){
		difficulty=5;
	}else if(sig->get_data()=="normal"){
		difficulty=4;
	}else if(sig->get_data()=="easy"){
		difficulty=3;
	}else if(sig->get_data()=="PVP"){
		AI_mode=2;
	}else if(sig->get_data()=="PVA"){
		AI_mode=0;
	}else if(sig->get_data()=="AVA"){
		AI_mode=1;
	}else if(sig->get_data()=="auto_AVA"){
		AI_mode=3;
	}else if(sig->get_data()=="undo"){
		next_step.clear();
		selected=false;
		chess_board->undo();
	}else if(sig->get_data()=="restart"){
		next_step.clear();
		selected=false;
		chess_board->restart();
	}else if(sig->get_data()=="auto"){
		next_step.clear();
		selected=false;
		AI_move(chess_board->cur_player);
	}else if(sig->get_data()=="edit"){
		next_step.clear();
		selected=false;
		edit_mode^=1;
	}else if(sig->get_data()=="chess"){
		edit_chess^=1;
	}else if(sig->get_data()=="play_chess"){
		selected=false;
		next_step.clear();
		delete chess_board;
		chess_board=new ChessBoard(9,3,10);
		chess_board->load_script(CM::folder_path+"game/chess/chessBoard/boardscript.txt");
	}else if(sig->get_data()=="play_chineseChess"){
		selected=false;
		next_step.clear();
		delete chess_board;
		chess_board=new ChineseChess();
		//chess_board->load_script(CM::folder_path+"game/chineseChess/chessBoard/boardscript.txt");
	}
	//std::cerr<<"SceneStart::handle_signal 2"<<std::endl;
	//std::cout<<sig->get_data()<<std::endl;
}
void SceneStart::next_turn(CM::Step step){
	chess_board->next_turn(step);

}
void SceneStart::camera_control(){
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
		camera->v += (float) (-0.01f * sqrt(camera->look_dis() + 0.001))
				* camera->look_vec_xz();
	}
	if(input->mouse->screen_pos.y<-0.95){
		camera->v += (float) (0.01f * sqrt(camera->look_dis() + 0.001))
				* camera->look_vec_xz();
	}
	if(input->mouse->screen_pos.x>0.95){
		camera->v += (float) (-0.01f * sqrt(camera->look_dis() + 0.001))
		* glm::cross(camera->look_vec_xz(), glm::vec3(0, 1, 0));
	}
	if(input->mouse->screen_pos.x<-0.95){
		camera->v += (float) (0.01f * sqrt(camera->look_dis() + 0.001))
		* glm::cross(camera->look_vec_xz(), glm::vec3(0, 1, 0));
	}
	if (input->mouse->right_pressed()) {
		camera->v += (float) (0.0005f * sqrt(camera->look_dis() + 0.001)
				* input->mouse->pos_delta().y) * camera->look_vec_xz();
		camera->v += (float) (-0.0005f * sqrt(camera->look_dis() + 0.001)
				* input->mouse->pos_delta().x)
				* glm::cross(camera->look_vec_xz(), glm::vec3(0, 1, 0));
	}

	///*


	//*/
	if (input->mouse->scroll) {
		camera->dis_alter_v += sqrt(camera->look_dis() + 0.1)
				* (0.05 * input->mouse->scroll);
	}
	if(camera->look_at.x>chess_board->cube_size*chess_board->size.x){
		if(camera->v.x>0.0f){
			camera->v.x*=-0.9f;
		}
	}else if(camera->look_at.x<0.0f){
		if(camera->v.x<0.0f){
			camera->v.x*=-0.9f;
		}
	}
	if(camera->look_at.z>chess_board->cube_size*chess_board->size.z){
		if(camera->v.z>0.0f){
			camera->v.z*=-0.9f;
		}
	}else if(camera->look_at.z<0.0f){
		if(camera->v.z<0.0f){
			camera->v.z*=-0.9f;
		}
	}
}
void SceneStart::AI_move(int player){
	selected=false;
	if(!ai->searching){
		ai->search_done=false;
		thread_pool->push_task(new CM::TaskAI(ai,thread_pool,chess_board,player,difficulty,MAX));
		//CM::Step best=ai->find_best_step(chess_board,player,difficulty,player*MAX);

	}
}
void SceneStart::handle_input(){
	if(edit_mode){
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
	}else{
		if(input->mouse->left_clicked()){
			int tmpsx=chess_board->selected_piece.x;
			int tmpsy=chess_board->selected_piece.y;;
			if(tmpsx>=0&&tmpsy>=0&&tmpsx<chess_board->chess_board->sizex&&
					tmpsy<chess_board->chess_board->sizey){
				prev_sx=s.x;
				prev_sy=s.y;
				s.x=chess_board->selected_piece.x;
				s.y=chess_board->selected_piece.y;
				if(selected){
					for(unsigned i=0;i<next_step.size();i++){
						if(next_step.at(i).selected(s.x,s.y)){
							selected=false;
							next_turn(next_step.at(i));
							break;
						}
					}
				}
				if(s.x>=0&&s.y>=0&&s.x<chess_board->chess_board->sizex&&
						s.y<chess_board->chess_board->sizey){
					int type=chess_board->chess_board->get(s.x,s.y);
					if(type*chess_board->cur_player>0){
						next_step.clear();
						chess_board->find_next_step(chess_board->chess_board,
								s.x,s.y,next_step);
						selected=true;
					}else{
						selected=false;
					}
				}


			}

		}
	}
	if(input->keyboard->get('E')){
		edit_mode^=1;
	}
	if(input->keyboard->get('Q')){
		edit_chess^=1;
	}
	if(input->keyboard->get('0')){
		AI_mode=0;
	}
	if(input->keyboard->get('1')){
		AI_mode=1;
	}
	if(input->keyboard->get('2')){
		AI_mode=2;
	}
	if(input->keyboard->get('S')){
		//chess_board->save_board(CM::folder_path+"game/chess/chessBoard/board.txt");
		chess_board->save_board(CM::folder_path+"game/chineseChess/chessBoard/board.txt");
	}
	if(input->keyboard->get('L')){
		//chess_board->load_board(CM::folder_path+"game/chess/chessBoard/board.txt");
		chess_board->load_board(CM::folder_path+"game/chineseChess/chessBoard/board.txt");
	}
	if(input->keyboard->get(Input::KeyCode::Plus)){
		if(edit_chess&&chess_type<(int)chess_board->pieces.size()){
			chess_type++;
		}else if(type<chess_board->cube_type_num){
			type++;
		}

	}
	if(input->keyboard->get(Input::KeyCode::Minus)&&type>0){
		if(edit_chess&&chess_type>0){
			chess_type--;
		}else if(type>0){
			type--;
		}
	}
	camera_control();
}
void SceneStart::scene_update(){
	handle_input();
	camera->update();

	UI->update_UIObject();
	chess_board->find_select_cube();
	chess_board->winner=chess_board->check_winner(chess_board->chess_board);
	if(ai->search_done){
		next_turn(ai->best_step);
		ai->search_done=false;
		std::cout<<"total_compute="<<ai->total_compute<<std::endl;
	}
	if(chess_board->winner==0){
		if(AI_mode==0){
			if(chess_board->cur_player==-1){
				AI_move(chess_board->cur_player);
			}else{
				camera=p1camera;
				draw->set_camera(camera);
			}
		}else if(AI_mode==1){
			AI_move(chess_board->cur_player);
		}else if(AI_mode==3){
			if(chess_board->steps.size()>150){
				int score=chess_board->evaluate_score(chess_board->chess_board,chess_board->cur_player);
				if(score>40){
					chess_board->backpropagation();
					chess_board->restart();
				}else if(chess_board->steps.size()>250){
					chess_board->restart();
				}else{
					AI_move(chess_board->cur_player);
				}
			}else{
				/*
				if(chess_board->steps.size()>10){
					chess_board->restart();
				}else{
					AI_move(chess_board->cur_player);
				}
				*/
				AI_move(chess_board->cur_player);
			}
		}else if(AI_mode==2){
			if(chess_board->cur_player==1){
				camera=p1camera;
				draw->set_camera(camera);
			}else{
				camera=p2camera;
				draw->set_camera(camera);
			}
		}
	}else{
		if(AI_mode==3){
			chess_board->restart();
		}
	}
}
void SceneStart::scene_draw(){
	if(ai->searching){
		float time_used=(glfwGetTime()-ai->start_time);
		draw->push(new Display::RenderString("AI thinking time:"+Tim::String::to_string(time_used),
				0.02,glm::vec2(0,0.95)));
	}else{
		if(chess_board->cur_player==1){
			draw->push(new Display::RenderString("player1's turn",0.02,glm::vec2(0,0.95)));
		}else{
			draw->push(new Display::RenderString("player2's turn",0.02,glm::vec2(0,0.95)));
		}
	}

	if(difficulty==3){
		draw->push(new Display::RenderString("Easy AI",0.02,glm::vec2(0.4,0.95)));
	}else if(difficulty==4){
		draw->push(new Display::RenderString("Normal AI",0.02,glm::vec2(0.4,0.95)));
	}else if(difficulty==5){
		draw->push(new Display::RenderString("Normal+ AI",0.02,glm::vec2(0.4,0.95)));
	}else if(difficulty==6){
		draw->push(new Display::RenderString("Hard AI",0.02,glm::vec2(0.4,0.95)));
	}

	draw->push(new Display::RenderString(Tim::String::to_string(chess_board->selected_piece.x)+","+
	Tim::String::to_string(chess_board->selected_piece.y),0.02,glm::vec2(0.6,0.95)));
	if(edit_mode){
		if(edit_chess){
			static Position pos=Position(glm::vec3(), glm::vec3());
			pos.set_pos(glm::vec3((chess_board->selected_on.x+0.5f)*chess_board->cube_size,
					  (chess_board->selected_on.y+0.5f)*chess_board->cube_size,
					  (chess_board->selected_on.z+0.5f)*chess_board->cube_size));

			if(chess_type>0)chess_board->pieces.at(chess_type-1)->draw(&pos,!destruct_mode);
			draw->push(new Display::RenderString("Edit Chess",0.02,glm::vec2(0.7,0.95)));
		}else{
			draw->push(new Display::RenderString("Edit Board",0.02,glm::vec2(0.7,0.95)));
		}
	}


	int score=chess_board->evaluate_score(chess_board->chess_board,chess_board->cur_player);
	draw->push(new Display::RenderString("score:"+Tim::String::to_string(score),0.02,glm::vec2(0,0.85)));
	draw->push(new Display::RenderString("turn:"+Tim::String::to_string((int)chess_board->steps.size()),
			0.02,glm::vec2(0.2,0.85)));
	if(chess_board->winner!=0){
		if(chess_board->winner==1)draw->push(new Display::RenderString("player1 win!!",0.05,glm::vec2(0.3,0.5)));
		else draw->push(new Display::RenderString("player2 win!!",0.05,glm::vec2(0.3,0.5)));
	}
	UI->draw_UIObject(draw);
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


	CM::Step *step;
	if(!chess_board->steps.empty()){
		step=chess_board->steps.back();
		step->draw_step(glm::vec3(0.4,0.4,0.6));
		if(chess_board->steps.size()>=2){
			step=chess_board->steps.at(chess_board->steps.size()-2);
			step->draw_step(glm::vec3(0.4,0.6,0.4));
		}
	}
	if(selected){
		draw_step();
	}
}
void SceneStart::draw_step(){
	Display::CubeLight* cl;
	cl=new Display::CubeLight();
	cl->size=1.01f*chess_board->cube_size;
	cl->color=glm::vec3(0.5,0.5,0.5);
	cl->pos=glm::vec3((s.x+0.5f)*chess_board->cube_size,
					  (2.5f)*chess_board->cube_size,
					  (s.y+0.5f)*chess_board->cube_size);
	lightControl->push_temp_light(cl);
	for(unsigned i=0;i<next_step.size();i++){
		next_step.at(i).draw_next_step();
	}
}


}
} /* namespace CM */
