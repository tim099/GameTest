#include "class/game/chessMaster/scene/SceneStart.h"
#include "class/game/chessMaster/common.h"
#include "class/display/light/LightControl.h"
#include "class/display/draw/drawObject/AllDrawObjects.h"
#include "class/tim/math/Position.h"
namespace CM {
namespace scene{
SceneStart::SceneStart() {
	UI = 0;
	local_path = std::string("scene/start/");
	chess_board = 0;
	camera = 0;
	lightControl = 0;
	destruct_mode=false;
	type=1;
	sx=0,sy=0,selected=false;
	prev_sx=0;prev_sy=0;
}
SceneStart::~SceneStart() {

}
void SceneStart::scene_initialize() {
	//draw->Enable3D=false;
	int sizex=8,sizey=3,sizez=8;
	chess_board=new ChessBoard(sizex,sizey,sizez);
	//chess_board->load_board(CM::folder_path+"game/chess/chessBoard/board");
	chess_board->load_script(CM::folder_path+"game/chess/chessBoard/boardscript.txt");
	glm::vec3 pos=glm::vec3(0.5*chess_board->cube_size*sizex,6,-3);
	camera = new Camera(pos,
			pos+glm::vec3(0,-4,0.5f*sizez), glm::vec3(0, 1, 0), 60.0, 0.1f,
			10000.0f);
	lightControl = new LightControl(120);
	lightControl->shadow_dis=3.0f;
	lightControl->push_light(
			new ParallelLight(glm::vec3(1.0, -1.2, 0.2),
					glm::vec3(0.6, 0.6, 0.6), true));
	lightControl->push_light(
			new ParallelLight(glm::vec3(-0.5, -0.5, 2.1),
					glm::vec3(1.1, 1.1, 1.1), true));
	lightControl->push_light(
			new ParallelLight(glm::vec3(-0.2, -1.2, -1.1),
					glm::vec3(0.9, 0.9, 0.9), true));
	lightControl->push_light(
			new ParallelLight(glm::vec3(0.5, -0.4, -0.7),
					glm::vec3(0.4, 0.4, 0.4), true));
	draw->Enable3D = true;
	draw->set_camera(camera);
	draw->set_lightControl(lightControl);
	UI = new UI::UI(CM::folder_path+local_path+"UI/startUI.txt");
	UI->Enable_Mode(UI::Mode::EDIT);
}
void SceneStart::scene_terminate() {

	delete chess_board;
	delete camera;
	delete lightControl;
	delete UI;
}
void SceneStart::pause(){

}
void SceneStart::resume(){

}
void SceneStart::handle_signal(Signal *sig){
	std::cout<<sig->get_data()<<std::endl;
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
		camera->v += (float) (-0.02f * sqrt(camera->look_dis() + 0.001))
				* camera->look_vec_xz();
	}
	if(input->mouse->screen_pos.y<-0.95){
		camera->v += (float) (0.02f * sqrt(camera->look_dis() + 0.001))
				* camera->look_vec_xz();
	}
	if(input->mouse->screen_pos.x>0.95){
		camera->v += (float) (-0.02f * sqrt(camera->look_dis() + 0.001))
		* glm::cross(camera->look_vec_xz(), glm::vec3(0, 1, 0));
	}
	if(input->mouse->screen_pos.x<-0.95){
		camera->v += (float) (0.02f * sqrt(camera->look_dis() + 0.001))
		* glm::cross(camera->look_vec_xz(), glm::vec3(0, 1, 0));
	}
	if (input->mouse->right_pressed()) {
		camera->v += (float) (0.001f * sqrt(camera->look_dis() + 0.001)
				* input->mouse->pos_delta().y) * camera->look_vec_xz();
		camera->v += (float) (-0.001f * sqrt(camera->look_dis() + 0.001)
				* input->mouse->pos_delta().x)
				* glm::cross(camera->look_vec_xz(), glm::vec3(0, 1, 0));
	}
	if(input->keyboard->get('S')){
		chess_board->save_board(CM::folder_path+"game/chess/chessBoard/board");
	}
	if(input->keyboard->get('L')){
		chess_board->load_board(CM::folder_path+"game/chess/chessBoard/board");
	}
	///*
	if (input->mouse->left_clicked()) {//->left_pressed()
		if(!destruct_mode){
			/*
			chess_board->set_type(chess_board->selected_on.x,
								chess_board->selected_on.y,
								chess_board->selected_on.z,
								type);
			 */
			/*
			chess_board->chess_board->get(chess_board->selected_on.x,
					chess_board->selected_on.z)=type;
			*/
			/*
			int x=chess_board->selected_cube.x;
			int z=chess_board->selected_cube.z;
			int type=chess_board->chess_board->get(x,z);
			std::vector<glm::ivec2> next_step;
			if(type!=0){
				bool player1=true;
				if(type<0){
					type*=-1;
					player1=false;
				}
				type-=1;
				chess_board->pieces.at(type)->next_step(glm::ivec2(x,z),next_step,player1);
			}
			*/
			prev_sx=sx;
			prev_sy=sy;
			sx=chess_board->selected_cube.x;
			sy=chess_board->selected_cube.z;
			if(selected){
				for(unsigned i=0;i<next_step.size();i++){
					if(sx==next_step.at(i).x&&
					   sy==next_step.at(i).y){
						selected=false;
						type=chess_board->get_type(prev_sx,prev_sy);
						chess_board->set_type(prev_sx,prev_sy,0);
						chess_board->set_type(sx,sy,type);
						break;
					}
				}
			}
			if(chess_board->chess_board->get(sx,sy)!=0){
				selected=true;
			}else{
				selected=false;
			}

		}else{
			prev_sx=sx;
			prev_sy=sy;
			sx=chess_board->selected_cube.x;
			sy=chess_board->selected_cube.z;
			if(selected){
				for(unsigned i=0;i<next_step.size();i++){
					if(sx==next_step.at(i).x&&
					   sy==next_step.at(i).y){
						selected=false;
						type=chess_board->get_type(prev_sx,prev_sy);
						chess_board->set_type(prev_sx,prev_sy,0);
						chess_board->set_type(sx,sy,type);
						break;
					}
				}
			}
			if(chess_board->chess_board->get(sx,sy)!=0){
				selected=true;
			}else{
				selected=false;
			}
			/*
			int x=chess_board->selected_cube.x;
			int z=chess_board->selected_cube.z;
			int type=chess_board->chess_board->get(x,z);
			std::vector<glm::ivec2> next_step;
			if(type!=0){
				bool player1=true;
				if(type<0){
					type*=-1;
					player1=false;
				}
				type-=1;
				chess_board->pieces.at(type)->next_step(glm::ivec2(x,z),next_step,player1);
			}
			*/
			/*
			chess_board->chess_board->get(chess_board->selected_on.x,
					chess_board->selected_on.z)=-type;
			*/
			/*
			chess_board->set_type(chess_board->selected_cube.x,
								chess_board->selected_cube.y,
								chess_board->selected_cube.z,
							    0);
			*/
		}

	}
	if(input->keyboard->get('Q')&&type<11){
		type++;
	}
	if(input->keyboard->get('E')&&type>1){
		type--;
	}
	//*/
	if (input->mouse->scroll) {
		camera->dis_alter_v += sqrt(camera->look_dis() + 0.1)
				* (0.05 * input->mouse->scroll);
	}
	if(camera->look_at.x>chess_board->cube_size*chess_board->board->sizex){
		if(camera->v.x>0.0f){
			camera->v.x*=-0.9f;
		}
	}else if(camera->look_at.x<0.0f){
		if(camera->v.x<0.0f){
			camera->v.x*=-0.9f;
		}
	}
	if(camera->look_at.z>chess_board->cube_size*chess_board->board->sizez){
		if(camera->v.z>0.0f){
			camera->v.z*=-0.9f;
		}
	}else if(camera->look_at.z<0.0f){
		if(camera->v.z<0.0f){
			camera->v.z*=-0.9f;
		}
	}
}
void SceneStart::handle_input(){
	camera_control();
}
void SceneStart::scene_update(){
	handle_input();
	camera->update();
	UI->update_UIObject();
	chess_board->find_select_cube();

}
void SceneStart::scene_draw(){
	CubeLight* cl=new CubeLight();
	cl->size=1.01f*chess_board->cube_size;
	lightControl->push_temp_light(cl);
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

	UI->draw_UIObject(draw);
	chess_board->draw();
	static Position pos=Position(glm::vec3(), glm::vec3());
	pos.set_pos(glm::vec3((chess_board->selected_on.x+0.5f)*chess_board->cube_size,
			  (chess_board->selected_on.y+0.5f)*chess_board->cube_size,
			  (chess_board->selected_on.z+0.5f)*chess_board->cube_size));

	//chess_board->pieces.at(type-1)->draw(&pos,!destruct_mode);
	if(selected){
		draw_step();
	}
}
void SceneStart::draw_step(){
	//std::cout<<"selected="<<sx<<","<<sy<<std::endl;
	int type=chess_board->chess_board->get(sx,sy);
	next_step.clear();
	bool player1=true;
	if(type<0){
		type*=-1;
		player1=false;
	}
	type-=1;
	chess_board->pieces.at(type)->next_step(glm::ivec2(sx,sy),next_step,player1);
	CubeLight* cl;
	cl=new CubeLight();
	cl->size=1.01f*chess_board->cube_size;
	lightControl->push_temp_light(cl);
	cl->color=glm::vec3(1,1,0);
	cl->pos=glm::vec3((sx+0.5f)*chess_board->cube_size,
					  (2.5f)*chess_board->cube_size,
					  (sy+0.5f)*chess_board->cube_size);
	for(unsigned i=0;i<next_step.size();i++){
		cl=new CubeLight();
		cl->size=1.01f*chess_board->cube_size;
		lightControl->push_temp_light(cl);
		int type2=chess_board->get_type(next_step.at(i).x,next_step.at(i).y);
		if(chess_board->chess_board->get(sx,sy)*type2<0){
			cl->color=glm::vec3(1,0,0);
		}else{
			cl->color=glm::vec3(0,1,0);
		}

		cl->pos=glm::vec3((next_step.at(i).x+0.5f)*chess_board->cube_size,
						  (2.5f)*chess_board->cube_size,
						  (next_step.at(i).y+0.5f)*chess_board->cube_size);



	}


}


}
} /* namespace CM */
